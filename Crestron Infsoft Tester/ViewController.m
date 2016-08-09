//
//  ViewController.m
//  Crestron Infsoft Tester
//
//  Created by Victor Wang on 8/8/16.
//  Copyright © 2016 Victor Wang. All rights reserved.
//

#import "ViewController.h"

@interface ViewController()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    resultArr = [[NSMutableArray alloc]init];
    
    ILLocationServiceManager* locationServiceManager = [ILLocationServiceManager getInstance];
    locationServiceManager.apiKey = @"d1eebea2-380f-42ad-aa3f-00844f5d37fc";
    
    _locationManager = [ILLocationManager new];
    [_locationManager requestLocationUpdates:self minTime:100 minDistance:0];
    
    _mapView = [[MapView alloc] initWithFrame:CGRectMake(0, 150, self.view.frame.size.width, self.view.frame.size.height)];
    _mapView.clipsToBounds = TRUE;
    _mapView.apiKey = @"d1eebea2-380f-42ad-aa3f-00844f5d37fc";
    [_mapView setMinZoomLevel:25];
    [_mapView setMaxZoomLevel:15];
    [_mapView setDisplayButton3D:TRUE];
    [_mapView setDisplayButtonLevelWheel:TRUE];
    [_mapView setDisplayPOIs:TRUE];
    [_mapView setDisplayButtonMyPosition:TRUE];
    
    
    
    [self.view insertSubview:_mapView atIndex:0];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onLocationChanged:(ILLocation *)location{
    if(location == NULL || !location.valid)
        return;
    
    //update the labels in the main view with current position
    NSString *latString = [NSString stringWithFormat:@"%lf", location.latitude];
    _lattitudeLabel.text = latString;
    NSString *longString = [NSString stringWithFormat:@"%lf", location.longitude];
    _longitudeLabel.text = longString;
    
    NSLog(@"my location is lat=%lf, lon=%lf, level=%d", location.latitude, location.longitude, location.level);
    
    //move the map to the correct location
    MyLocation* myLocation = [MyLocation new];
    myLocation.latitude = location.latitude;
    myLocation.longitude = location.longitude;
    myLocation.level = location.level;
    myLocation.orientationInDegrees = 90;
    myLocation.hasOrientation = TRUE;
    
    [_mapView setTrackingMode:MapTrackingModePosition];
    [_mapView animateToMyLocation:myLocation];
}

//refresh the location labels to the crrent position
- (IBAction)refreshLocation:(id)sender{
    ILLocation *currentLoc = _locationManager.getLastKnownLocation;
    
    NSString *latString = [NSString stringWithFormat:@"%lf", currentLoc.latitude];
    _lattitudeLabel.text = latString;
    NSString *longString = [NSString stringWithFormat:@"%lf", currentLoc.longitude];
    _longitudeLabel.text = longString;
}

//record current position into memory
- (IBAction)recordNewLocation:(id)sender{
    ILLocation *currentLoc = _locationManager.getLastKnownLocation;
    
    NSString *latString = [NSString stringWithFormat:@"%lf", currentLoc.latitude];
    _lattitudeLabel.text = latString;
    NSString *longString = [NSString stringWithFormat:@"%lf", currentLoc.longitude];
    _longitudeLabel.text = longString;
    
    [resultArr addObject:latString];
    [resultArr addObject:longString];
    
    _numPositionLabel.text = [NSString stringWithFormat:@"%d", [_numPositionLabel.text intValue]+1];
}

//remove last location data recorded
- (IBAction)deleteLastLocation:(id)sender{
    if(resultArr.count >= 2){
        [resultArr removeLastObject];
        [resultArr removeLastObject];
        _numPositionLabel.text = [NSString stringWithFormat:@"%d", [_numPositionLabel.text intValue]-1];
    }
}

//send location data through email
- (IBAction)emailLocationData:(id)sender{
    if([MFMailComposeViewController canSendMail]) {
        MFMailComposeViewController *mailCont = [[MFMailComposeViewController alloc] init];
        mailCont.mailComposeDelegate = self;
        
        //build location data in csv format
        NSMutableString *resultStr = [[NSMutableString alloc]init];
        for(NSString *str in resultArr){
            [resultStr appendString:str];
            [resultStr appendString:@", "];
        }
        
        [mailCont setSubject:@"Infsoft Location Data"];
        [mailCont setToRecipients:[NSArray arrayWithObject:@"vwang@crestron.com"]];
        [mailCont setMessageBody:resultStr isHTML:NO];
        
        [self presentViewController:mailCont animated:YES completion:nil];
    }
}

//after the email interface has been dismissed
- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error {
    //clear out location data
    [resultArr removeAllObjects];
    _numPositionLabel.text = [NSString stringWithFormat:@"%d", 0];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
