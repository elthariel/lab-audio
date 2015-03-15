# Introduction #
libthc is a gtk widget library oriented torward audio

# Details #
Current widget:
  * Slider
  * Label

Current helper:
  * SkinManager : store and share all Skin instance (and images)
  * ModeManager : change the mode (connect/normal/slime) of each widget
  * WidgetManager : store and share each widget, his name, his path, allow to find them using regexp
  * OSCManager : allow communication between widget out-process
  * LearnManager : allow midi learn (merge with ModeManager)
  * InputManager : take input from kbdz; dispatch to each widget

# Dependencies #
  * gtkmm
  * libsigc++
  * libxml++
  * `boost/shared_ptr`
  * boost/format
  * boost/filesystem
  * libsvgr

# Doc #
## Slider ##
Parameter:
> value : the value of the slider
Extension:
> parameter's dnd and paste/cut

Mode:
> all : use one image for each state
> handle: use one image for the background, one for the handle
> foreground: use one image for the background, one to display the foreground % value
> vector: simple cairo mode
Example:
```
  Thc::Slider slider2(Thc::Images::create_images("../skins/bang/fader-%i.png", 127), Thc::Param::create_param(), false, true);
  Thc::Slider slider3(Thc::Images::create_images("../skins/mixxx/poti_%i.png", 12), Thc::Param::create_param(), true);
  Thc::Slider slider4(Thc::Images::create_images("../skins/mixxx/vu%il.png", 32), Thc::Param::create_param(), false, true);
  Thc::Slider slider5(Thc::Images::create_images("../skins/mixxx/vu%ir.png", 32), Thc::Param::create_param(), false);
  Thc::Slider slider6(Thc::Param::create_param(), false);
  Thc::Slider slider7(Thc::Image::create_image("../skins/mixxx/slider_back_horiz.png"),
  				       Thc::Image::create_image("../skins/mixxx/slider_handle_horiz.png"),
  				       Thc::Param::create_param(),
  				       Thc::Slider::SliderHandle,
  				       true,
  				       false);
  Slider slider8(Thc::Image::create_image("../skins/mixxx/slider_back_vert.png"),
  				       Thc::Image::create_image("../skins/mixxx/slider_handle_vert.png"),
  				       Thc::Param::create_param(),
  				       Thc::Slider::SliderHandle,
  				       false,
  				       true);
  Thc::Slider slider9(Thc::SkinManager::instance()->get_skin("slider/crossfader-full"));
```

## ModeManager ##
> The skin manager allow to group widgets.
> You can define group and toggle the mode of each separetely
Example:
```
  Thc::ModeManager::instanciate();
  Thc::Slider slider1, slider2;

  Thc::ModeManager::instance()->add_widget("/group1", slider1);
  Thc::ModeManager::instance()->add_widget("/group1", slider2);

  Thc::ModeManager::instance()->set_mode("/group1", ModeNormal);
  Thc::ModeManager::instance()->set_mode("/group1", ModeConnect);
```

## SkinManager ##
> The skin manager is used to provide skin support to all widget.
> He store each skin instance.
```
  Thc::SkinManager::instanciate();
  Thc::SkinManager::instance()->load_path("../skins");

  Thc::Slider slider(Thc::SkinManager::instance()->get_skin("slider/crossfader-full"));
```

## WidgetManager ##
> The WidgetManager
Example:
```
  Thc::WidgetManager::instanciate();

  Thc::WidgetManager::instance()->get_widget("/container0/collapsable2/Slider4");
```

## OSCManager ##
> The OSCManager use the WidgetManager to dispatch message to widget. It use liblo to communicate between process, and internal call for inprocess communication

Example:
```
  Thc::OSCManager::instanciate();  //that's all
```


# TODO #
## First Release Goal ##
  * slider, knob, pad, port\_matrix (simple input/output port display)
  * midi learn
  * dnd, copy/paste using XDND and xml
  * dnd port
  * balloon windows for each port
  * define different kind of port, and virtual port (for plugins)
  * find each widget which match with a regexp
  * list all available skin for a widget

## General ##
  * implement a better draw\_ports
  * allow to connect port using drag'n'drop
  * add WIDGETs: button, label, padXY, automation, keyboard, peak vu, wave visualisation, wave summary
  * add CONTAINERs: Container, Collapsable
  * write a doc/doxygen comment
  * regroup all audio wigdet already written for gtk that will fit in the project
  * optional: menu for ModeGroup/SkinManager
  * dont segfault when file not found

## IThcWidget/ThcWidget ##
  * add a name to each port parameter
  * autobind each param value change to queue\_draw
  * display a balloon for each port

## Skin ##
  * load\_images on demand to reduce memory usage

## ModeManager ##

## SkinManager ##

## OSCManager ##
  * implement
  * support dnd paste/cut between widget (of two differents process)
  * support to connect to widget (of two differents process)

## WidgetManager ##
  * implement
  * store as hashmap : [name](widget.md) [shared\_ptr

&lt;widget&gt;

, widget path]
  * associate name to each widget instance
  * allow regexp match ("/slider**"), ("/slider[1-9]"), etc..)
  * used by OSCManager to dispatch message
  * used by the InputManager to dispatch message**

## LearnManager/InputManager ##
  * implement
  * allow midi/osc learn
  * use one signal
  * could be merged with the ModeManager?

## Slider ##
  * support infinite mode
  * use Color::Ptr everywhere
  * rename or typedef Knob or something like that

## Container ##
  * autorearange widget
  * support toggle fullscreen
  * support always on top
  * support moving widget

## Collapsable ##