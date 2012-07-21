
(function() {
 
 ormma = window.ormma = {};
 
 var mraid = window.mraid = {};
 
 // CONSTANTS ///////////////////////////////////////////////////////////////
 
 var STATES = mraid.STATES = {
 LOADING     :'loading',
 DEFAULT     :'default',
 EXPANDED    :'expanded',
 HIDDEN      :'hidden'	
 };
 
 var EVENTS = mraid.EVENTS = {
 READY				:'ready',
 ERROR              :'error',
 INFO               :'info',
 STATECHANGE        :'stateChange',
 VIEWABLECHANGE		:'viewableChange'
 };
 
 
 var CONTROLS = mraid.CONTROLS = {
 BACK    :'back',
 FORWARD :'forward',
 REFRESH :'refresh',
 ALL     :'all'
 };
 
 var FEATURES = mraid.FEATURES = {
 LEVEL1      :'level-1',
 LEVEL2      :'level-2',
 LEVEL3      :'level-3',
 SCREEN      :'screen',
 ORIENTATION :'orientation',
 HEADING     :'heading',
 LOCATION    :'location',
 SHAKE       :'shake',
 TILT        :'tilt',
 NETWORK     :'network',
 SMS         :'sms',
 PHONE       :'phone',
 EMAIL       :'email',
 CALENDAR    :'calendar',
 CAMERA      :'camera',
 AUDIO       :'audio',
 VIDEO       :'video',
 MAP         :'map'
 };
 
 var NETWORK = mraid.NETWORK = {
 OFFLINE :'offline',
 WIFI    :'wifi',
 CELL    :'cell',
 UNKNOWN :'unknown'
 };
 
 // PRIVATE PROPERTIES (sdk controlled) //////////////////////////////////////////////////////
 
 var state = STATES.LOADING;
 
 var size = {
 width:0,
 height:0
 };
 
 var defaultPosition = {
 x:0,
 y:0,
 width:0,
 height:0
 };
 
 var maxSize = {
 width:0,
 height:0
 };
 
 var supports = {
 'level-1':true,
 'level-2':true,
 'level-3':true,
 'screen':true,
 'orientation':true,
 'heading':true,
 'location':true,
 'shake':true,
 'tilt':true,
 'network':true,
 'sms':true,
 'phone':true,
 'email':true,
 'calendar':true,
 'camera':true,
 'audio':true,
 'video':true,
 'map':true
 };
 
 var heading = -1;
 
 var keyboardState = false;
 
 var location = null;
 
 var network = NETWORK.UNKNOWN;
 
 var orientation = -1;
 
 var screenSize = null;
 
 var shakeProperties = null;
 
 var tilt = null;
 
 var assets = {};
 
 var cacheRemaining = -1;
 
 var viewable = false;
 
 // PRIVATE PROPERTIES (internal) //////////////////////////////////////////////////////
 
 var intervalID = null;
 var readyTimeout = 10000;
 var readyDuration = 0;
 
 function trim(str) {
 return str.replace(/^\s+|\s+$/g,"");
 }
 
 var dimensionValidators = {
 x:function(value) { return !isNaN(value) && value >= 0; },
 y:function(value) { return !isNaN(value) && value >= 0; },
 width:function(value) { return !isNaN(value) && value >= 0},
 height:function(value) { return !isNaN(value) && value >= 0}
 };
 
 var expandPropertyValidators = {
 useBackground:function(value) { return (value === true || value === false); },
 backgroundColor:function(value) { return (typeof value == 'string' && value.substr(0,1) == '#' && !isNaN(parseInt(value.substr(1), 16))); },
 backgroundOpacity:function(value) { return !isNaN(value) && value >= 0 && value <= 1; },
 lockOrientation:function(value) { return (value === true || value === false); }
 };
 
 var shakePropertyValidators = {
 intensity:function(value) { return !isNaN(value); },
 interval:function(value) { return !isNaN(value); }
 };
 
 var changeHandlers = {
 state:function(val) {
 if (state == STATES.LOADING) {
 intervalID = window.setInterval(window.mraid.signalReady, 20);
 broadcastEvent(EVENTS.INFO, 'controller initialized, attempting callback');
 }
 broadcastEvent(EVENTS.INFO, 'setting state to ' + stringify(val));
 state = val;
 broadcastEvent(EVENTS.STATECHANGE, state);
 },
 size:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting size to ' + stringify(val));
 size = val;
 broadcastEvent(EVENTS.SIZECHANGE, size.width, size.height);
 },
 defaultPosition:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting default position to ' + stringify(val));
 defaultPosition = val;
 },
 maxSize:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting maxSize to ' + stringify(val));
 maxSize = val;
 },
 expandProperties:function(val) {
 broadcastEvent(EVENTS.INFO, 'merging expandProperties with ' + stringify(val));
 for (var i in val) {
 expandProperties[i] = val[i];
 }
 },
 supports:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting supports to ' + stringify(val));
 supports = {};
 for (var key in FEATURES) {
 supports[FEATURES[key]] = contains(FEATURES[key], val);
 }
 },
 heading:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting heading to ' + stringify(val));
 heading = val;
 broadcastEvent(EVENTS.HEADINGCHANGE, heading);
 },
 keyboardState:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting keyboardState to ' + stringify(val));
 keyboardState = val;
 broadcastEvent(EVENTS.KEYBOARDCHANGE, keyboardState);
 },
 location:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting location to ' + stringify(val));
 location = val;
 broadcastEvent(EVENTS.LOCATIONCHANGE, location.lat, location.lon, location.acc);
 },
 network:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting network to ' + stringify(val));
 network = val;
 broadcastEvent(EVENTS.NETWORKCHANGE, (network != NETWORK.OFFLINE && network != NETWORK.LOADING), network);
 },
 orientation:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting orientation to ' + stringify(val));
 orientation = val;
 broadcastEvent(EVENTS.ORIENTATIONCHANGE, orientation);
 },
 screenSize:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting screenSize to ' + stringify(val));
 screenSize = val;
 broadcastEvent(EVENTS.SCREENCHANGE, screenSize.width, screenSize.height);
 },
 shakeProperties:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting shakeProperties to ' + stringify(val));
 shakeProperties = val;
 },
 tilt:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting tilt to ' + stringify(val));
 tilt = val;
 broadcastEvent(EVENTS.TILTCHANGE, tilt.x, tilt.y, tilt.z);
 },
 cacheRemaining:function(val) {
 broadcastEvent(EVENTS.INFO, 'setting cacheRemaining to ' + stringify(val));
 cacheRemaining = val;
 },
 viewable:function(val) {
 broadcastEvent(EVENTS.VIEWABLECHANGE, 'setting viewable to ' + stringify(val));
 viewable = val;
 }
 };
 
 var listeners = {};
 
 var EventListeners = function(event) {
 this.event = event;
 this.count = 0;
 var listeners = {};
 
 this.add = function(func) {
 var id = String(func);
 if (!listeners[id]) {
 listeners[id] = func;
 this.count++;
 if (this.count == 1) ormmaview.activate(event);
 }
 };
 this.remove = function(func) {
 var id = String(func);
 if (listeners[id]) {
 listeners[id] = null;
 delete listeners[id];
 this.count--;
 if (this.count == 0) ormmaview.deactivate(event);
 return true;
 } else {
 return false;
 }
 };
 this.removeAll = function() { for (var id in listeners) this.remove(listeners[id]); };
 this.broadcast = function(args) { for (var id in listeners) listeners[id].apply({}, args); };
 this.toString = function() {
 var out = [event,':'];
 for (var id in listeners) out.push('|',id,'|');
 return out.join('');
 };
 };
 
 // PRIVATE METHODS ////////////////////////////////////////////////////////////
 
 ormmaview.addEventListener('change', function(properties) {
                            for (var property in properties) {
                            var handler = changeHandlers[property];
                            handler(properties[property]);
                            }
                            });
 
 ormmaview.addEventListener('shake', function() {
                            broadcastEvent(EVENTS.SHAKE);
                            });
 
 ormmaview.addEventListener('error', function(message, action) {
                            broadcastEvent(EVENTS.ERROR, message, action);
                            });
 
 ormmaview.addEventListener('response', function(uri, response) {
                            broadcastEvent(EVENTS.RESPONSE, uri, response);
                            });
 
 ormmaview.addEventListener('assetReady', function(alias, URL) {
                            assets[alias] = URL;
                            broadcastEvent(EVENTS.ASSETREADY, alias);
                            });
 
 ormmaview.addEventListener('assetRemoved', function(alias) {
                            assets[alias] = null;
                            delete assets[alias];
                            broadcastEvent(EVENTS.ASSETREMOVED, alias);
                            });
 
 ormmaview.addEventListener('assetRetired', function(alias) {
                            assets[alias] = null;
                            delete assets[alias];
                            broadcastEvent(EVENTS.ASSETRETIRED, alias);
                            });
 
 var clone = function(obj) {
 var f = function() {};
 f.prototype = obj;
 return new f();
 };
 
 var stringify = function(obj) {
 if (typeof obj == 'object') {
 if (obj.push) {
 var out = [];
 for (var p in obj) {
 out.push(obj[p]);
 }
 return '[' + out.join(',') + ']';
 } else {
 var out = [];
 for (var p in obj) {
 out.push('\''+p+'\':'+obj[p]);
 }
 return '{' + out.join(',') + '}';
 }
 } else {
 return String(obj);
 }
 };
 
 var valid = function(obj, validators, action, full) {
 /*
  if (full) {
  if (obj === undefined) {
  broadcastEvent(EVENTS.ERROR, 'Required object missing.', action);
  return false;
  } else {
  for (var i in validators) {
  if (obj[i] === undefined) {
  broadcastEvent(EVENTS.ERROR, 'Object missing required property ' + i, action);
  return false;
  }
  }
  }
  }
  for (var i in obj) {
  if (!validators[i]) {
  broadcastEvent(EVENTS.ERROR, 'Invalid property specified - ' + i + '.', action);
  return false;
  } else if (!validators[i](obj[i])) {
  broadcastEvent(EVENTS.ERROR, 'Value of property ' + i + ' is not valid type.', action);
  return false;
  }
  }
  */
 return true;
 };
 
 var contains = function(value, array) {
 for (var i in array) if (array[i] == value) return true;
 return false;
 };
 
 var broadcastEvent = function() {
 var args = new Array(arguments.length);
 for (var i = 0; i < arguments.length; i++) args[i] = arguments[i];
 var event = args.shift();
 if (listeners[event]) listeners[event].broadcast(args);
 }
 
 // LEVEL 1 ////////////////////////////////////////////////////////////////////
 
 
 mraid.signalReady = function() {
 
 window.clearInterval(intervalID);
 broadcastEvent (EVENTS.READY, 'SDK Ready');
 broadcastEvent(EVENTS.INFO, 'callback invoked');
 
 
 };
 
 mraid.addEventListener = function(event, listener) {
 if (!event || !listener) {
 broadcastEvent(EVENTS.ERROR, 'Both event and listener are required.', 'addEventListener');
 } else if (!contains(event, EVENTS)) {
 broadcastEvent(EVENTS.ERROR, 'Unknown event: ' + event, 'addEventListener');
 } else {
 if (!listeners[event]) listeners[event] = new EventListeners(event);
 listeners[event].add(listener);
 }
 };
 
 mraid.close = function() {
 ormmaview.close();
 };
 
 mraid.expand = function(dimensions, URL) {
 broadcastEvent(EVENTS.INFO, 'expanding to ' + stringify(dimensions));
 
 var frame = {
     x:0,
     y:0,
     width:mraid.getScreenSize().width,
     height:mraid.getScreenSize().height
 };
 
 ormmaview.expand(frame, URL);
 
 };
 
 mraid.getDefaultPosition = function() {
 return clone(defaultPosition);
 };
 
 mraid.getExpandProperties = function() {
 return clone(ormmaview.getExpandProperties());
 };
 
 mraid.getMaxSize = function() {
 return clone(maxSize);
 };
 
 mraid.getSize = function() {
 return clone(size);
 };
 
 mraid.getState = function() {
 return state;
 };
 
 mraid.hide = function() {
 if (state == STATES.HIDDEN) {
 broadcastEvent(EVENTS.ERROR, 'Ad is currently hidden.', 'hide');
 } else {
 ormmaview.hide();
 }
 };
 
 mraid.open = function(URL, controls) {
 if (!URL) {
 broadcastEvent(EVENTS.ERROR, 'URL is required.', 'open');
 } else {
 ormmaview.open(URL, controls);
 }
 };
 
 
 mraid.openMap = function(POI, fullscreen) {
 if (!POI) {
 broadcastEvent(EVENTS.ERROR, 'POI is required.', 'openMap');
 } else {
 ormmaview.openMap(POI, fullscreen);
 }
 };
 
 
 mraid.removeEventListener = function(event, listener) {
 if (!event) {
 broadcastEvent(EVENTS.ERROR, 'Must specify an event.', 'removeEventListener');
 } 
 else {
 if (listener && (!listeners[event] || !listeners[event].remove(listener))) {
 broadcastEvent(EVENTS.ERROR, 'Listener not currently registered for event', 'removeEventListener');
 return;  
 } 
 else if (listeners[event]){
 listeners[event].removeAll();
 }
 
 if (listeners[event] && listeners[event].count == 0) {
 listeners[event] = null;
 delete listeners[event];
 }
 }
 };
 
 
 mraid.resize = function(width, height) {
 if (width == null || height == null || isNaN(width) || isNaN(height) || width < 0 || height < 0) {
 broadcastEvent(EVENTS.ERROR, 'Requested size must be numeric values between 0 and maxSize.', 'resize');
 } else if (width > maxSize.width || height > maxSize.height) {
 broadcastEvent(EVENTS.ERROR, 'Request (' + width + ' x ' + height + ') exceeds maximum allowable size of (' + maxSize.width +  ' x ' + maxSize.height + ')', 'resize');
 } else if (width == size.width && height == size.height) {
 broadcastEvent(EVENTS.ERROR, 'Requested size equals current size.', 'resize');
 } else {
 ormmaview.resize(width, height);
 }
 };
 
 mraid.setExpandProperties = function(properties) {
 if (valid(properties, expandPropertyValidators, 'setExpandProperties')) {
 ormmaview.setExpandProperties(properties);
 }
 };
 
 mraid.show = function() {
 if (state != STATES.HIDDEN) {
 broadcastEvent(EVENTS.ERROR, 'Ad is currently visible.', 'show');
 } else {
 ormmaview.show();
 }
 };
 
 mraid.playAudio = function(URL, properties) {
 if (!supports[FEATURES.AUDIO]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'playAudio');
 } else if (!URL || typeof URL != 'string') {
 broadcastEvent(EVENTS.ERROR, 'Request must specify a URL', 'playAudio');
 } else {
 ormmaview.playAudio(URL, properties);
 }
 };
 
 
 mraid.playVideo = function(URL, properties) {
 if (!supports[FEATURES.VIDEO]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'playVideo');
 } else if (!URL || typeof URL != 'string') {
 broadcastEvent(EVENTS.ERROR, 'Request must specify a URL', 'playVideo');
 } else {
 ormmaview.playVideo(URL, properties);
 }
 };
 
 
 // LEVEL 2 ////////////////////////////////////////////////////////////////////
 
 mraid.createEvent = function(date, title, body) {
 title = trim(title);
 body = trim(body);
 if (!supports[FEATURES.CALENDAR]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'createEvent');
 } else if (!date || typeof date != 'object' || !date.getDate) {
 broadcastEvent(EVENTS.ERROR, 'Valid date required.', 'createEvent');
 } else if (!title || typeof title != 'string' || title.length == 0) {
 broadcastEvent(EVENTS.ERROR, 'Valid title required.', 'createEvent');
 }	else if (!body || typeof body != 'string' || body.length == 0) {
 broadcastEvent(EVENTS.ERROR, 'Valid body required.', 'createEvent');
 } else {
 ormmaview.createEvent(date, title, body);
 }
 };
 
 mraid.getHeading = function() {
 if (!supports[FEATURES.HEADING]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getHeading');
 }
 return heading;
 };
 
 mraid.getKeyboardState = function() {
 if (!supports[FEATURES.LEVEL2]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getKeyboardState');
 }
 return keyboardState;
 }
 
 mraid.getLocation = function() {
 if (!supports[FEATURES.LOCATION]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getLocation');
 }
 return (null == location)?null:clone(location);
 };
 
 mraid.getNetwork = function() {
 if (!supports[FEATURES.NETWORK]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getNetwork');
 }
 return network;
 };
 
 mraid.getOrientation = function() {
 if (!supports[FEATURES.ORIENTATION]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getOrientation');
 }
 return orientation;
 };
 
 mraid.getScreenSize = function() {
 if (!supports[FEATURES.SCREEN]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getScreenSize');
 } else {
 return (null == screenSize)?null:clone(screenSize);
 }
 };
 
 mraid.getShakeProperties = function() {
 if (!supports[FEATURES.SHAKE]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getShakeProperties');
 } else {
 return (null == shakeProperties)?null:clone(shakeProperties);
 }
 };
 
 mraid.getTilt = function() {
 if (!supports[FEATURES.TILT]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getTilt');
 } else {
 return (null == tilt)?null:clone(tilt);
 }
 };
 
 mraid.makeCall = function(number) {
 if (!supports[FEATURES.PHONE]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'makeCall');
 } else if (!number || typeof number != 'string') {
 broadcastEvent(EVENTS.ERROR, 'Request must provide a number to call.', 'makeCall');
 } else {
 ormmaview.makeCall(number);
 }
 };
 
 mraid.sendMail = function(recipient, subject, body) {
 if (!supports[FEATURES.EMAIL]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'sendMail');
 } else if (!recipient || typeof recipient != 'string') {
 broadcastEvent(EVENTS.ERROR, 'Request must specify a recipient.', 'sendMail');
 } else {
 ormmaview.sendMail(recipient, subject, body);
 }
 };
 
 mraid.sendSMS = function(recipient, body) {
 if (!supports[FEATURES.SMS]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'sendSMS');
 } else if (!recipient || typeof recipient != 'string') {
 broadcastEvent(EVENTS.ERROR, 'Request must specify a recipient.', 'sendSMS');
 } else {
 ormmaview.sendSMS(recipient, body);
 }
 };
 
 
 mraid.setShakeProperties = function(properties) {
 if (!supports[FEATURES.SHAKE]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'setShakeProperties');
 } else if (valid(properties, shakePropertyValidators, 'setShakeProperties')) {
 ormmaview.setShakeProperties(properties);
 }
 };
 
 //    ormma.storePicture = function(URL) {};
 
 mraid.supports = function(feature) {
 if (supports[feature]) {
 return true;
 } else {
 return false;
 }
 };
 
 // LEVEL 3 ////////////////////////////////////////////////////////////////////
 
 mraid.addAsset = function(URL, alias) {
 if (!URL || !alias || typeof URL != 'string' || typeof alias != 'string') {
 broadcastEvent(EVENTS.ERROR, 'URL and alias are required.', 'addAsset');
 } else if (supports[FEATURES.LEVEL3]) {
 ormmaview.addAsset(URL, alias);
 } else if (URL.indexOf('ormma://') == 0) {
 broadcastEvent(EVENTS.ERROR, 'Native device assets not supported by this client.', 'addAsset');
 } else {
 assets[alias] = URL;
 broadcastEvent(EVENTS.ASSETREADY, alias);
 }
 };
 
 mraid.addAssets = function(assets) {
 for (var alias in assets) {
 mraid.addAsset(assets[alias], alias);
 }
 };
 
 mraid.getAssetURL = function(alias) {
 if (!assets[alias]) {
 broadcastEvent(EVENTS.ERROR, 'Alias unknown.', 'getAssetURL');
 }
 return assets[alias];
 };
 
 mraid.getCacheRemaining = function() {
 if (!supports[FEATURES.LEVEL3]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'getCacheRemaining');
 }
 return cacheRemaining;
 };
 
 mraid.request = function(uri, display) {
 if (!supports[FEATURES.LEVEL3]) {
 broadcastEvent(EVENTS.ERROR, 'Method not supported by this client.', 'request');
 } else if (!uri || typeof uri != 'string') {
 broadcastEvent(EVENTS.ERROR, 'URI is required.', 'request');
 } else {
 ormmaview.request(uri, display);
 }
 };
 
 mraid.removeAllAssets = function() {
 for (var alias in assets) {
 mraid.removeAsset(alias);
 }
 };
 
 mraid.removeAsset = function(alias) {
 if (!alias || typeof alias != 'string') {
 broadcastEvent(EVENTS.ERROR, 'Alias is required.', 'removeAsset');
 } else if (!assets[alias]) {
 broadcastEvent(EVENTS.ERROR, 'Alias unknown.', 'removeAsset');
 } else if (supports[FEATURES.LEVEL3]) {
 ormmaview.removeAsset(alias);
 } else {
 assets[alias] = null;
 delete assets[alias];
 broadcastEvent(EVENTS.ASSETREMOVED, alias);
 }
 };
 
 mraid.isViewable = function() {
 return viewable;
 };
 
 })();