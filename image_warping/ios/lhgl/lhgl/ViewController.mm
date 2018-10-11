//
//  ViewController.m
//  lhgl
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//
#import <AVFoundation/AVFoundation.h>
#import "ViewController.h"
#include "context.hpp"
#include "interface_render.hpp"
#include "../../render/render/core/timer.hpp"

@interface ViewController () <AVCaptureVideoDataOutputSampleBufferDelegate>
{
    struct ESContext _esContext;
    Timer _timer;
}
@property (nonatomic,strong) AVCaptureSession *session;
@property (nonatomic,strong) AVCaptureDevice *device;
@property (nonatomic,strong) AVCaptureDeviceInput *input;
@property (nonatomic,strong) AVCaptureVideoDataOutput *output;
@property (nonatomic,strong) dispatch_queue_t queue ;
@property (nonatomic,strong) AVCaptureConnection *connection;
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

-(void) setup_gl;
-(void) tear_down_gl;
-(void) setup_camera;
-(void) change_worlds;
@end

@implementation ViewController
CInterfaceRender _triangle;
unsigned char* _image_address;
int _width;
int _height;

- (void)viewDidLoad {
    [super viewDidLoad];
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!self.context){
        NSLog(@"failed to create es context");
    }
    
    GLKView *view = (GLKView*)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    [self setup_gl];
    [self setup_camera];
    UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(locationChange:)];
    pan.delaysTouchesBegan = YES;
    [self.view addGestureRecognizer:pan];
}

//改变位置
-(void)locationChange:(UIPanGestureRecognizer*)p
{
    //[[UIApplication sharedApplication] keyWindow]
    UIView *move = self.view;
    CGPoint panPoint = [p locationInView:self.view];
    if(p.state == UIGestureRecognizerStateBegan)
    {
        
    }
    else if (p.state == UIGestureRecognizerStateEnded)
    {
        //[self performSelector:@selector(changeColor) withObject:nil afterDelay:4.0];//
    }
    if(p.state == UIGestureRecognizerStateChanged)
    {
        //move.center = CGPointMake(panPoint.x, panPoint.y);
    }
    else if(p.state == UIGestureRecognizerStateEnded)
    {
        
    }
}

-(void) dealloc{
    [self tear_down_gl];
    if (self.context == [EAGLContext currentContext]){
        [EAGLContext setCurrentContext:nil];
    }
    
    if (NULL != _image_address){
        delete [] _image_address;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && ([[self view] window] == nil)){
        self.view = nil;
        [self tear_down_gl];
        
        if (self.context == [EAGLContext currentContext]){
            [EAGLContext setCurrentContext:nil];
        }
        
        self.context = nil;
    }
}

- (void)setup_camera {
    self.queue = dispatch_queue_create("video_process",DISPATCH_QUEUE_SERIAL);
    self.session= [[AVCaptureSession alloc] init];
    self.session.sessionPreset = AVCaptureSessionPreset1280x720;
    
    NSArray *devices =[AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *device in devices) {
        if (device.position == AVCaptureDevicePositionFront) {
            self.device = device;
            break;
        }
    }
    
    [self.session beginConfiguration];
    
    self.input = [AVCaptureDeviceInput deviceInputWithDevice:self.device error:NULL];
    [self.session addInput:self.input];
    
    self.output = [[AVCaptureVideoDataOutput alloc] init];
    [self.output setSampleBufferDelegate:self queue:self.queue];
    self.output.videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:                            [NSNumber numberWithInt:kCVPixelFormatType_32BGRA], kCVPixelBufferPixelFormatTypeKey,nil                      ];
    [self.output setAlwaysDiscardsLateVideoFrames:NO];
    
    if ([self.session canAddOutput:self.output]) {
        [self.session addOutput:self.output];
    }
    
    self.connection =  [self.output connectionWithMediaType:AVMediaTypeVideo];
    if ([self.connection isVideoOrientationSupported]) {
        [self.connection setVideoOrientation:AVCaptureVideoOrientationPortrait];
    }
    
    [self.session commitConfiguration];
    
    [self.session startRunning];
}

-(void) setup_gl{
    [EAGLContext setCurrentContext:self.context];
    memset(&_esContext, 0, sizeof(_esContext));
    NSString *dir = [[NSBundle mainBundle] bundlePath];
    
    NSString *modelPath = [[NSBundle mainBundle] pathForResource:@"megviifacepp_0_4_7_model" ofType:@""];
    NSData *modelData = [NSData dataWithContentsOfFile:modelPath];
    if (modelData != nil){
        _esContext.model_bytes = modelData.bytes;
        _esContext._model_datas_length = modelData.length;
    }
    
    NSString* documentpath  = NSSearchPathForDirectoriesInDomains ( NSDocumentDirectory , NSUserDomainMask , YES ).firstObject;
    
    //NSString *model_path = [[NSBundle mainBundle] pathForResource:@"boblampclean" ofType:@"md5mesh"];
    //_esContext.srcfile = [model_path cStringUsingEncoding:NSASCIIStringEncoding];
    _esContext.appdir = [dir cStringUsingEncoding:NSASCIIStringEncoding];
    _esContext.writedir = [documentpath cStringUsingEncoding:NSASCIIStringEncoding];
    _esContext.width = 640;//640
    _esContext.height = 1136;//1136;
    _triangle.esMain(&_esContext);
}
- (void)tear_down_gl
{
    [EAGLContext setCurrentContext:self.context];
    _esContext.shutdown();
}


-(void)update{
    _esContext.update();
    //_esContext.keyboard(true, 0, 1);
}

-(void) change_worlds{
    static int worlds_sign = 0;
    if (_timer.count_time()){
        switch(worlds_sign){
            case 0:
                worlds_sign =  1;
                _esContext.set_color(1.0, 0.0, 0.0);
                _esContext.update_worlds(100, 900, L"科大讯飞@！#123ABCEfg");
                break;
            case 1:
                worlds_sign =  2;
                _esContext.set_color(0.0, 1.0, 0.0);
                _esContext.update_worlds(100, 900, L"发财致富，奔小康");
                break;
            case 2:
                worlds_sign =  3;
                _esContext.set_color(0.0, 0.0, 1.0);
                _esContext.update_worlds(100, 900, L"你好啊哈哈哈哈");
                break;
            case 3:
                worlds_sign =  0;
                _esContext.set_color(1.0, 1.0, 0.0);
                _esContext.update_worlds(100, 900, L"牛奶盒子");
                break;
            default:
                break;
        }
        _timer.set_count_time(500);
    }
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
    //printf("glkView:\t\t%x \t%x. \n", self.context, [EAGLContext currentContext]);
    _esContext.width = view.drawableWidth;
    _esContext.height = view.drawableHeight;
    if (NULL != _image_address){
        _esContext.video_frame(_image_address, _width, _height);
    }
    
    [self change_worlds];
    _esContext.draw();
    
}

- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    //printf("captureOutput:\t%x \t%x. \n", self.context, [EAGLContext currentContext]);
    if ([EAGLContext currentContext] != self.context) {
        [EAGLContext setCurrentContext:self.context];
    }
    CVPixelBufferRef buffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(buffer, 0);
    _image_address = (unsigned char*)(CVPixelBufferGetBaseAddress(buffer));
    _width = (int)CVPixelBufferGetWidth(buffer);
    _height = (int)CVPixelBufferGetHeight(buffer);
    OSType ty = CVPixelBufferGetPixelFormatType(buffer);
    //_esContext.video_frame(_image_address, _width, _height);
    CVPixelBufferUnlockBaseAddress(buffer, 0);
    
}



@end
