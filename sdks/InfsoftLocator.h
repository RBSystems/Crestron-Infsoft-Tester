//
//  InfsoftLocator.h
//  InfsoftLocator
//
//  Created by Tobias Donaubauer/infsoft on 04/03/14.
//  Last Update: 05/06/2016
//  Copyright (c) 2014 infsoft. All rights reserved.
//

#ifndef InfsoftLocator_InfsoftLocator_h
#define InfsoftLocator_InfsoftLocator_h

/*! @header InfsoftLocator.h
 @availability example
 */

/*!
 ILLocation of an object.
 */
@interface ILLocation : NSObject

/*!
 @property latitude
 Indicating the latitude of the object.
 */
@property double latitude;
/*!
 @property longitude
 Indicating the longitude of the object.
 */
@property double longitude;
/*!
 @property level
 Indicating the level of the object.
 */
@property int level;
/*!
 @property accuracyInMeters
 Indicating the accuracy in metres of the location.
 */
@property float accuracyInMeters;
/*!
 @property posSourceKind
 Indicating the poistion source kind of the object.
 */
@property int posSourceKind;
/*!
 @property orientationInDegree
 Indicating the orientation of the object in degree.
 */
@property double orientationInDegree;
/*!
 @property valid
 If this is NO, the location is not valid.
 */
@property BOOL valid;
/*!
 @property extra
 Contains extra stuff for the location.
 */
@property NSMutableArray* extra;

@end

#define ILLocationServiceManager_UseGPS         0x01
#define ILLocationServiceManager_UseBLE         0x02
#define ILLocationServiceManager_UseAll         (ILLocationServiceManager_UseGPS|ILLocationServiceManager_UseBLE)


typedef enum{
    ILLocationManagerState_NotInit,
    ILLocationManagerState_StartingUp,
    ILLocationManagerState_BeaconsNotConfigured,
    ILLocationManagerState_Running
}ILLocationManagerState;

/*!
 @protocol ILLocationListener
 @discussion This gets called when a location changes.
 */
@protocol ILLocationListener  <NSObject>

/*!
 @function onLocationChanged:
 @param location This is the new location.
 */
-(void)onLocationChanged:(ILLocation*)location;

@end

/*!
 ILLocationServiceManager.
 */
@interface ILLocationServiceManager : NSObject // added : NSObject to make the auto doc work!!

/*!
 @property apiKey
 */
@property NSString* apiKey;
/*!
 @function getInstance
 @result Returns instance of LocationServiceManager.
 */
+(ILLocationServiceManager*)getInstance;

+(ILLocationServiceManager*)getInstance:(int)flags;

@end

/*!
 ILLocationManager.
 */
@interface ILLocationManager : NSObject

/*!
 @function requestLocationUpdates:minTime:minDistance:
 @param locationListener Listener for location changes.
 @param minTime Lowest possible time.
 @param minDistance Lowest ppossible distance.
 */
-(void)requestLocationUpdates:(id<ILLocationListener>)locationListener minTime:(long)minTime minDistance:(float)minDistance;
/*!
 @function removeLocationUpdates:
 @param locationListener Listener for location changes.
 */
-(void)removeLocationUpdates:(id<ILLocationListener>)locationListener;
/*!
 @function getLastKnownLocation
 @result Returns the location which was the last to be known.
 */
-(ILLocation*)getLastKnownLocation;

+(ILLocationManagerState) getState;

@end

#endif
