//
//  GOinsideMaps.h
//  GOinsideMap
//
//  Created by Tobias Donaubauer/infsoft on 10/12/12.
//  Last Update: 12/06/16
//  Copyright (c) 2012 infsoft. All rights reserved.
//

#ifndef GOinsideMap_GOinsideMaps_h
#define GOinsideMap_GOinsideMaps_h

/*! @header InfsoftMaps.h
 @availability example
 */


@interface GMDebugFlag : NSObject

+(void)setDebugFlag:(BOOL)on;
+(BOOL)isDebugFlag;

@end


/*!
 UID of a GOinside object.
 */
@interface UID : NSObject

/*!
 @function toString
 @result A string representing the UID.
 */
-(NSString*) toString;

@end


/*!
 Pin on map.
 */
@interface MapPin : NSObject

/*!
 @property latitude
 Indicating the location of the pin.
 */
@property double latitude;
/*!
 @property longitude
 Indicating the location of the pin.
 */
@property double longitude;
/*!
 @property level
 Indicating the location of the pin.
 */
@property int level;
/*!
 @property tag
 Tag of the pin.
 */
@property id<NSObject> tag;

@end

/*!
 A geopoint.
 */
@interface GeoPoint : NSObject

/*!
 @property latitude
 Indicating the location of the point.
 */
@property double latitude;
/*!
 @property longitude
 Indicating the location of the point.
 */
@property double longitude;
/*!
 @property level
 Indicating the location of the point.
 */
@property int level;

/*!
 @function initWith:longitude:level:
 Returns an object of GeoPoint.
 @param lat This defines the latitude of the GeoPoint.
 @param lon This defines the longitude of the GeoPoint.
 @param lev This defines the level of the GeoPoint.
 @result A reference to a GeoPoint object.
 */
-(id)initWith:(double)lat longitude:(double)lon level:(int)lev;

@end

/*!
 A Projection.
 */
@interface Projection : NSObject

/*!
 @function toPixels:
 Returns an object of CGPoint.
 @param geoPoint Defines the GeoPoint which should be represented as CGPoint.
 @result A reference to a CGPoint object.
 */
-(CGPoint) toPixels:(GeoPoint*)geoPoint;
/*!
 @function toPixels:longitude:
 Returns an object of CGPoint.
 @param lat Defines the latitude which should be represented within the CGPoint.
 @param lon Defines the longitude which should be represented within the CGPoint.
 @result A reference to a CGPoint object.
 */
-(CGPoint) toPixels:(double)lat longitude:(double)lon;
/*!
 @function formPixels:
 Returns an object of GeoPoint.
 @param point Defines the CGPoint which should be represented as a GeoPoint.
 @result A reference to a CGPoint object.
 */
-(GeoPoint*)fromPixels:(CGPoint)point;


@end

/*!
 The MapLevel.
 */
@interface MapLevel : NSObject

/*!
 @property name
 Representing the name of the MapLevel.
 */
@property NSString* name;
/*!
 @property level
 Representing the level of the MapLevel.
 */
@property int level;

@end


/*!
 The MapAnnotation.
 */
@interface MapAnnotation : NSObject

/*!
 @property latitude
 Defines the latitude of the MapAnnotation.
 */
@property double latitude;
/*!
 @property longitude
 Defines the longitude of the MapAnnotation.
 */
@property double longitude;
/*!
 @property level
 Defines the level of the MapAnnotation.
 */
@property int level;
/*!
 @property tag
 Defines the tag of the MapAnnotation.
 */
@property id<NSObject> tag;
/*!
 @property headline
 Defines the headline of the MapAnnotation.
 */
@property NSString* headline;
/*!
 @property text
 Defines the describing text of the MapAnnotation.
 */
@property NSString* text;

@end

/*!
 The POIInfo.
 */
@interface POIInfo : NSObject

/*!
 @property propertiesByKey
 Defines a dictionary which includes all properties of the POIInfo.
 */
@property NSMutableDictionary* propertiesByKey;
/*!
 @property uid
 Defines the UID of the POIInfo.
 */
@property UID* uid;
/*!
 @property latitude
 Defines the latitude of the POIInfo.
 */
@property double latitude;
/*!
 @property longitude
 Defines the longitude of the POIInfo.
 */
@property double longitude;
/*!
 @property level
 Defines the level of the POIInfo.
 */
@property int level;

@end

/*!
 A MapBuilding.
 */
@interface MapBuilding : NSObject

/*!
 @property uid
 Defines the UID of the MapBuilding.
 */
@property UID* uid;
/*!
 @property levels
 Defines the levels of the MapBuilding.
 */
@property NSMutableArray* levels;
/*!
 @property properties
 Includes all properties of the MapBuilding.
 */
@property NSMutableDictionary* properties;

@end

/*!
 MyLocation.
 */
@interface MyLocation : GeoPoint

/*!
 @property accuracy
 Represents the accuracy of MyLocation.
 */
@property double accuracy;
/*!
 @property orientationInDegrees
 Represents the orientation in degrees of MyLocation.
 */
@property double orientationInDegrees;
/*!
 @property hasOrientation
 Shows if MyLocation has orientation.
 */
@property BOOL hasOrientation;

@end

/*!
 MapDrawOptions.
 */
@interface MapDrawOptions : NSObject

/*!
 @property routeDrawFloorChanges
 If this is NO, the route will not draw floor changes.
 */
@property BOOL routeDrawFloorChanges;
/*!
 @property routeDrawDestFlag
 If this is NO, the route will not draw a flag at destination.
 */
@property BOOL routeDrawDestFlag;
/*!
 @property routeColor
 Represents the route color of the route.
 */
@property UIColor* routeColor;
/*!
 @property routeHightlightedColor
 Represents the route color of the highlighted route.
 */
@property UIColor* routeHightlightedColor;


@end

/*!
 @protocol OnPOIClickListener
 @discussion This gets called when a POI is clicked.
 */
@protocol OnPOIClickListener  <NSObject>

/*!
 @function onPOIClick:
 This is the handler for clicking POIs. Information is shown.
 @param poiInfo This is a reference to a POIInfo object.
 
 This should coincide with the POI which was clicked.
 */
-(void)onPOIClick:(POIInfo*)poiInfo;

@end

/*!
 @protocol OnAnnotationClickListener
 @discussion This gets called when an annotation is clicked.
 */
@protocol OnAnnotationClickListener  <NSObject>

/*!
 @function onAnnotationClick:
 This is the handler for clicking annotations. Information is shown.
 @param tag This should coincide with the annotation which was clicked.
 */
-(void)onAnnotationClick:(id)tag;

@end

@protocol OfflineMapsListener  <NSObject>

-(void)onOfflineMapsDownloaded:(id)sender okay:(BOOL)okay;
-(void)onOfflineMapsDownload:(id)sender percentage:(float)percentage;

@end


@interface OfflineMaps : NSObject
{
    int failed;
    int success;
    int _revision;
    NSThread* _thread;
}

@property NSString* apiKey;
@property int maxZoomLevel;
@property id<OfflineMapsListener> delegate;

-(void)download;
-(BOOL)load;
-(UIImage*)getImage:(int)levelOfDetails tileX:(int)tileX tileY:(int)tileY level:(int)level;

@end



/*!
 @enum MapTrackingMode
 Includes all possible tracking modes for maps.
 @constant MapTrackingModeNone Only tracking.
 @constant MapTrackingModePosition Contains Position only.
 @constant MapTrackingModePositionAndCompass Contains position and compass.
 */
typedef enum{
    MapTrackingModeNone,
    MapTrackingModePosition,
    MapTrackingModePositionAndCompass
}MapTrackingMode;

/*!
 MapView.
 */
@interface MapView : UIView

/*!
 @property overlays
 Includes all overlays that are possible for the MapView.
 */
@property NSMutableArray* overlays;
/*!
 @property apiKey
 Represents the apiKey of the MapView as string.
 */
@property NSString* apiKey;
/*!
 @property onPOIClickListener
 Listener for clicks on POIs.
 */

@property NSMutableArray* serverOverlays;

@property id<OnPOIClickListener> onPOIClickListener;
/*!
 @property onAnnotationClickListener
 Listener for clicks on annotations.
 */
@property id<OnAnnotationClickListener> onAnnotationClickListener;

/*!
 @function animateTo:zoomLevel:
 @param geoPoint This defines the GeoPoint, which should be animated to.
 @param zoomLevel This defines the zoom level for the operation.
 */
-(void)animateTo:(GeoPoint*)geoPoint zoomLevel:(int)zoomLevel;
-(void)animateTo:(GeoPoint*)geoPoint zoomLevel:(int)zoomLevel animated:(BOOL)animated;

/*!
 @function animateToMyLocation:
 @param myLocation This defines the location, which should be animated to.
 @result If this returns NO, something is wrong ---------------------- example.
 */
-(BOOL)animateToMyLocation:(MyLocation*)myLocation;
/*!
 @function animateUse3D:
 @param use If this is no, 3D is not used.
 */
-(void)animateUse3D:(BOOL)use;

-(void)setServerTileExtURL:(NSString*)val;
-(NSString*)getServerTileExtURL;

// get methode
/*! 
 @function getBuilding
 @result A reference to a MapBuilding object.
*/
-(MapBuilding*)getBuilding;
/*!
 @function getLevel
 @result Integer to indicate the level.
 */
-(int)getLevel;
/*!
 @function getMapCenter
 @result A reference to a GeoPoint object.
 */
-(GeoPoint*)getMapCenter;
/*!
 @function getMyLocation
 @result A reference to a MyLocation object.
 */
-(MyLocation*)getMyLocation;
/*!
 @function getProjection
 @result A reference to a Projection object.
 */
-(Projection*)getProjection;
/*!
 @function getMyLocation
 @result Float to indicate the rotation.
 */
-(float)getRotationInDegrees;
/*!
 @function getRouteInfo
 @result Information about the route as string.
 */
-(NSString*)getRouteInfo;
/*!
 @function getZoomLevel
 @result Current zoom level.
 */
-(int)getZoomLevel;
/*!
 @function getHeight3D
 @result Current height.
 */
-(float)getHeight3D;
/*!
 @function isUse3D
 @result If this is NO, 3D is not used at the moment.
 */
-(BOOL)isUse3D;
/*!
 @function getDrawOptions
 @result Returns the currently used MapDrawOption.
 */
-(MapDrawOptions*)getDrawOptions;

// set methods
/*!
 @function setDisplayButton3D:
 @param on If this is No, the 3D button is not shown.
 */
-(void)setDisplayButton3D:(BOOL)on;
/*!
 @function setDisplayButtonLevelWheel:
 @param on If this is No, the button level wheel is not shown.
 */
-(void)setDisplayButtonLevelWheel:(BOOL)on;
/*!
 @function setDisplayButtonMyPosition:
 @param on If this is No, the button for my position is not shown.
 */
-(void)setDisplayButtonMyPosition:(BOOL)on;
/*!
 @function setDisplayPOIs:
 @param on If this is No, POIs are not shown.
 */
-(void)setDisplayPOIs:(BOOL)on;
/*!
 @function setLevel:
 @param level This is the current level.
 */
-(void)setLevel:(int)level;
/*!
 @function setMyLocation:
 @param myLocation This is the my current location.
 */
-(void)setMyLocation:(MyLocation*)myLocation;
/*!
 @function setRoute:
 @param xmlData This is data for the route in xml.
 */
-(void)setRoute:(NSString*)xmlData;
/*!
 @function setHighlightedRoutePart:
 @param xmlData This is data for the highlighted routepart in xml.
 */
-(void)setHighlightedRoutePart:(NSString*)xmlData;
/*!
 @function setRouteInfo:
 @param routeInfo This is information about the route.
 */
-(void)setRouteInfo:(NSString*)routeInfo;
/*!
 @function setValidDisplayRect:minLongitude:maxLatitude:maxLongitude:
 @param minLatitude This is the minimum latitude for the displayed rectangle.
 @param minLongitude This is the minimum longitude for the displayed rectangle.
 @param maxLatitude This is the maximum latitude for the displayed rectangle.
 @param maxLongitude This is the maximum longitude for the displayed rectangle.
 */
-(void)setValidDisplayRect:(double)minLatitude minLongitude:(double)minLongitude maxLatitude:(double)maxLatitude  maxLongitude:(double)maxLongitude;
/*!
 @function setMinZoomLevel:
 @param zoomLevel This is the lowest possible zoom level for the MapView.
 */
-(void)setMinZoomLevel:(int)zoomLevel;
/*!
 @function setMaxZoomLevel:
 @param zoomLevel This is the highest possible zoom level for the MapView.
 */
-(void)setMaxZoomLevel:(int)zoomLevel;

// display methods
/*!
 @function isDisplayButton3D
 @result If this returns NO, the 3Dbutton is not shown.
 */
-(BOOL)isDisplayButton3D;
/*!
 @function isDisplayButtonLevelWheel
 @result If this returns NO, the button level wheel is not shown.
 */
-(BOOL)isDisplayButtonLevelWheel;
/*!
 @function isDisplayButtonMyPosition
 @result If this returns NO, the button for my position is not shown.
 */
-(BOOL)isDisplayButtonMyPosition;
/*!
 @function isDisplayPOIs
 @result If this returns NO, the POIs are not shown.
 */
-(BOOL)isDisplayPOIs;

/*!
 @function setTrackingMode:
 @param trackingMode This is the trackingMode, which is getting set for the Map.
 */
-(void)setTrackingMode:(MapTrackingMode)trackingMode;
/*!
 @function getTrackingMode
 @result Returns the current tracking mode.
 */
-(MapTrackingMode)getTrackingMode;

/*!
 @function setPin:
 @param pin This is the pin, which is getting set on the Map.
 */
-(void)setPin:(MapPin*)pin;
/*!
 @function getPin
 @result Returns the MapPin.
 */
-(MapPin*)getPin;

/*!
 @function setMapAnnotation:
 @param annotation This is the annotation, which is getting set on the Map.
 */
-(void)setMapAnnotation:(MapAnnotation*)annotation;
/*!
 @function getMapAnnotation
 @result Returns the annotation.
 */
-(MapAnnotation*)getMapAnnotation;

/*!
 @function updateOverlay
 Refreshes overlay.
 */
-(void)updateOverlay;

/*!
 @function cleanUp
 Cleans up.
 */
-(void)cleanUp;

-(void)setOfflineMaps:(OfflineMaps*)offlineMaps;

@end

/*!
 Overlay for MapView.
 */
@interface Overlay : NSObject

/*!
 @function onDraw:mapView:useCache:
 @param context Context for map.
 @param mapView MapView for which the overlay gets set.
 @param useCache If this is NO, no caching will be use (can be slower then).
 */
-(void)onDraw:(CGContextRef)context mapView:(MapView*)mapView useCache:(BOOL)useCache;
/*!
 @function onSingleTap:mapView:
 @param point the point, where the user tapped.
 @param mapView The map on which the user tapped.
 @result If this returns NO, something is wrong ------- example.
 */
-(BOOL)onSingleTap:(CGPoint)point mapView:(MapView*)mapView;

@end


#endif
