//
//  bones_mesh.hpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef bones_mesh_hpp
#define bones_mesh_hpp

#include <stdio.h>
#include "texture.hpp"
#include <vector>
#include <map>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "math.hpp"

class BonesMesh{
public:
    BonesMesh();
    ~BonesMesh();
public:
    bool loadmesh(const std::string& Filename);
    
    void render();
    
    unsigned int num_bones() const
    {
        return _num_bones;
    }
    
    void bone_transform(float TimeInSeconds, std::vector<Matrix4f>& Transforms);
    
private:
#define NUM_BONES_PER_VEREX 4
    
    struct BoneInfo
    {
        Mat4f bone_offset;
        Mat4f final_transformation;
        BoneInfo(){
            bone_offset.zero();
            final_transformation.zero();
        }
    };
    
    struct VertexBoneData
    {
        unsigned int bone_id[NUM_BONES_PER_VEREX];
        float bone_weights[NUM_BONES_PER_VEREX];
        
        VertexBoneData()
        {
            Reset();
        };
        
        void Reset()
        {
            memset(bone_id, 0, sizeof(bone_id));
            memset(bone_weights, 0, sizeof(bone_weights));
        }
        
        void add_bone_data(unsigned int BoneID, float Weight);
    };
    
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
    void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform);
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int MeshIndex,
                  const aiMesh* paiMesh,
                  std::vector<Vector3f>& Positions,
                  std::vector<Vector3f>& Normals,
                  std::vector<Vector2f>& TexCoords,
                  std::vector<VertexBoneData>& Bones,
                  std::vector<unsigned int>& Indices);
    void LoadBones(unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<VertexBoneData>& Bones);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();
    
#define INVALID_MATERIAL 0xFFFFFFFF
    
    enum VB_TYPES {
        INDEX_BUFFER,
        POS_VB,
        NORMAL_VB,
        TEXCOORD_VB,
        BONE_VB,
        NUM_VBs
    };
    
    unsigned int _vao;
    unsigned int _vbos[NUM_VBs];
    
    struct MeshEntry {
        MeshEntry()
        {
            NumIndices    = 0;
            BaseVertex    = 0;
            BaseIndex     = 0;
            MaterialIndex = INVALID_MATERIAL;
        }
        
        unsigned int NumIndices;
        unsigned int BaseVertex;
        unsigned int BaseIndex;
        unsigned int MaterialIndex;
    };
    
    std::vector<MeshEntry> _entries;
    std::vector<TexureGl*> _textures;
    
    std::map<std::string,unsigned int> _bone_mapping; // maps a bone name to its index
    unsigned int _num_bones;
    std::vector<BoneInfo> _boneInfo;
    Matrix4f _global_inverse_transform;
    
    const aiScene* _scene;
    Assimp::Importer _importer;
};

#endif /* bones_mesh_hpp */
