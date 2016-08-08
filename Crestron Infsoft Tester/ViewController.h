//
//  ViewController.h
//  Crestron Infsoft Tester
//
//  Created by Victor Wang on 8/8/16.
//  Copyright © 2016 Victor Wang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "InfsoftLocator.h"
#import "InfsoftMaps.h"

@interface ViewController : UIViewController <ILLocationListener>
{
    ILLocationManager* _locationManager;
    MapView* _mapView;
    NSMutableArray *resultArr;
}

@property (strong, nonatomic) IBOutlet UILabel *lattitudeLabel;
@property (strong, nonatomic) IBOutlet UILabel *longitudeLabel;
@property (strong, nonatomic) IBOutlet UILabel *numPositionLabel;

@end

