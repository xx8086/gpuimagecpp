//
//  bones_mesh.cpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include <OpenGLES/ES3/gl.h>
#include "bones_mesh.hpp"
#include <sstream>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

void BonesMesh::VertexBoneData::add_bone_data(unsigned int BoneID, float Weight)
{
    for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(bone_id) ; i++) {
        if (bone_weights[i] == 0.0) {
            bone_id[i]     = BoneID;
            bone_weights[i] = Weight;
            return;
        }
    }
    
    // should never get here - more bones than we have space for
    assert(0);
}

BonesMesh::BonesMesh(){
    _vao = 0;
    memset(_vbos, 0, sizeof(_vbos));
    _num_bones = 0;
    _scene = NULL;
}


BonesMesh::~BonesMesh(){
    Clear();
}

void BonesMesh::Clear()
{
    for (unsigned int i = 0 ; i < _textures.size() ; i++) {
        SAFE_DELETE(_textures[i]);
    }
    
    if (_vbos[0] != 0) {
        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(_vbos), _vbos);
    }
    
    if (_vao != 0) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}


bool BonesMesh::loadmesh(const std::string& Filename)
{
    // Release the previously loaded mesh (if it exists)
    Clear();
    
    // Create the VAO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    // Create the buffers for the vertices attributes
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(_vbos), _vbos);
    
    bool Ret = false;
    
    _scene = _importer.ReadFile(Filename.c_str(), ASSIMP_LOAD_FLAGS);
    
    if (_scene) {
        _global_inverse_transform = Mat4f(_scene->mRootNode->mTransformation);
        _global_inverse_transform.Inverse();
        Ret = InitFromScene(_scene, Filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), _importer.GetErrorString());
    }
    
    // Make sure the VAO is not changed from the outside
    glBindVertexArray(0);
    
    return Ret;
}


bool BonesMesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
    _entries.resize(pScene->mNumMeshes);
    _textures.resize(pScene->mNumMaterials);
    
    std::vector<Vector3f> Positions;
    std::vector<Vector3f> Normals;
    std::vector<Vector2f> TexCoords;
    std::vector<VertexBoneData> Bones;
    std::vector<unsigned int> Indices;
    
    unsigned int NumVertices = 0;
    unsigned int NumIndices = 0;
    for (unsigned int i = 0 ; i < _entries.size() ; i++) {
        _entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
        _entries[i].NumIndices    = pScene->mMeshes[i]->mNumFaces * 3;
        _entries[i].BaseVertex    = NumVertices;
        _entries[i].BaseIndex     = NumIndices;
        
        NumVertices += pScene->mMeshes[i]->mNumVertices;
        NumIndices  += _entries[i].NumIndices;
    }
    

    Positions.reserve(NumVertices);
    Normals.reserve(NumVertices);
    TexCoords.reserve(NumVertices);
    Bones.resize(NumVertices);
    Indices.reserve(NumIndices);
    for (unsigned int i = 0 ; i < _entries.size() ; i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
    }
    
    if (!InitMaterials(pScene, Filename)) {
        return false;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[BONE_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(BONE_ID_LOCATION);
    glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
    glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
    glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    return 1;
}


void BonesMesh::InitMesh(unsigned int MeshIndex,
                           const aiMesh* paiMesh,
                           std::vector<Vector3f>& Positions,
                           std::vector<Vector3f>& Normals,
                           std::vector<Vector2f>& TexCoords,
                           std::vector<VertexBoneData>& Bones,
                           std::vector<unsigned int>& Indices)
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        
        Positions.push_back(Vector3f(pPos->x, pPos->y, pPos->z));
        Normals.push_back(Vector3f(pNormal->x, pNormal->y, pNormal->z));
        TexCoords.push_back(Vector2f(pTexCoord->x, pTexCoord->y));
    }
    
    LoadBones(MeshIndex, paiMesh, Bones);
    unsigned int basevertex = _entries[MeshIndex].BaseVertex;
    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0] + basevertex);
        Indices.push_back(Face.mIndices[1] + basevertex);
        Indices.push_back(Face.mIndices[2] + basevertex);
    }
}


void BonesMesh::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones){
    for (unsigned int i = 0 ; i < pMesh->mNumBones ; i++) {
        unsigned int bone_index = 0;
        std::string BoneName(pMesh->mBones[i]->mName.data);
        if (_bone_mapping.find(BoneName) == _bone_mapping.end()) {
            bone_index = _num_bones;
            _num_bones++;
            BoneInfo bi;
            _boneInfo.push_back(bi);
            _boneInfo[bone_index].bone_offset = Mat4f(pMesh->mBones[i]->mOffsetMatrix);
            _bone_mapping[BoneName] = bone_index;
        }
        else {
            bone_index = _bone_mapping[BoneName];
        }
        
        for (unsigned int j = 0 ; j < pMesh->mBones[i]->mNumWeights ; j++) {
            unsigned int vertex_id = _entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
            Bones[vertex_id].add_bone_data(bone_index, pMesh->mBones[i]->mWeights[j].mWeight);
        }
    }
}


bool BonesMesh::InitMaterials(const aiScene* pScene, const std::string& Filename){
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;
    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }
    
    bool Ret = true;
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        _textures[i] = NULL;
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string p(Path.data);
                if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }
                
                //p = "SmallDog_diff.tga";
                std::string FullPath = Dir + "/" + p;
                _textures[i] = new TexureGl;
                if (!_textures[i]->load_texture(FullPath)) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete _textures[i];
                    _textures[i] = NULL;
                    Ret = false;
                }
                else {
                    printf("%d - loaded texture '%s'\n", i, FullPath.c_str());
                }
            }
        }
    }
    
    return Ret;
}


void BonesMesh::render(){
    glBindVertexArray(_vao);
    int entries_size = _entries.size();
    for (unsigned int i = 0 ; i < entries_size; i++) {
        const unsigned int MaterialIndex = _entries[i].MaterialIndex;
        assert(MaterialIndex < _textures.size());
        if (_textures[MaterialIndex]) {
            _textures[MaterialIndex]->bind(GL_TEXTURE0);
        }
        
        glDrawElements(GL_TRIANGLES,
                       _entries[i].NumIndices,
                       GL_UNSIGNED_INT,
                       (void*)(sizeof(unsigned int) * _entries[i].BaseIndex));
    }
    
    glBindVertexArray(0);
}


unsigned int BonesMesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim){
    for (unsigned int i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
    return 0;
}


unsigned int BonesMesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim){
    assert(pNodeAnim->mNumRotationKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
    return 0;
}


unsigned int BonesMesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim){
    assert(pNodeAnim->mNumScalingKeys > 0);
    for (unsigned int i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
    return 0;
}


void BonesMesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }
    
    unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}


void BonesMesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}


void BonesMesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }
    
    unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    unsigned int NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}


void BonesMesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform){
    std::string NodeName(pNode->mName.data);
    const aiAnimation* pAnimation = _scene->mAnimations[0];
    Matrix4f NodeTransformation(pNode->mTransformation);
    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
    if (pNodeAnim) {
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        Mat4f ScalingM;
        ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);
        
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        Mat4f RotationM = Matrix4f(RotationQ.GetMatrix());

        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        Mat4f TranslationM;
        TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);
        NodeTransformation = TranslationM * RotationM * ScalingM;
    }
    
    Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;
    if (_bone_mapping.find(NodeName) != _bone_mapping.end()) {
        unsigned int BoneIndex = _bone_mapping[NodeName];
        _boneInfo[BoneIndex].final_transformation = _global_inverse_transform * GlobalTransformation * _boneInfo[BoneIndex].bone_offset;
    }
    
    for (unsigned int i = 0 ; i < pNode->mNumChildren ; i++) {
        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }
}


void BonesMesh::bone_transform(float TimeInSeconds, std::vector<Matrix4f>& Transforms){
    Matrix4f Identity;
    Identity.InitIdentity();
    float TicksPerSecond = (float)(_scene->mAnimations[0]->mTicksPerSecond != 0 ? _scene->mAnimations[0]->mTicksPerSecond : 25.0f);
    float TimeInTicks = TimeInSeconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, (float)_scene->mAnimations[0]->mDuration);
    ReadNodeHeirarchy(AnimationTime, _scene->mRootNode, Identity);
    Transforms.resize(_num_bones);
    for (unsigned int i = 0 ; i < _num_bones ; i++) {
        Transforms[i] = _boneInfo[i].final_transformation;
    }
}


const aiNodeAnim* BonesMesh::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName){
    for (unsigned int i = 0 ; i < pAnimation->mNumChannels ; i++) {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
        if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
            return pNodeAnim;
        }
    }
    
    return NULL;
}
