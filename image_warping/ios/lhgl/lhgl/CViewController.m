//
//  CViewController.m
//  KYBeautifulDemo
//
//  Created by gongdeyin on 2018/9/26.
//  Copyright © 2018 gongdeyin. All rights reserved.
//

#import "CViewController.h"
#import <AVFoundation/AVFoundation.h>

@interface CViewController () <AVCaptureVideoDataOutputSampleBufferDelegate>
@property (nonatomic,strong) AVCaptureSession *session;
@property (nonatomic,strong) AVCaptureDevice *device;
@property (nonatomic,strong) AVCaptureDeviceInput *input;
@property (nonatomic,strong) AVCaptureVideoDataOutput *output;
@property (nonatomic,strong) dispatch_queue_t queue ;
@property (nonatomic,strong) AVCaptureConnection *connection;
@end

@implementation CViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setup];
}

- (void)setup {
  
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

- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    CVPixelBufferRef *buffer = CMSampleBufferGetImageBuffer(sampleBuffer);
  NSLog(@"11");
}
@end
