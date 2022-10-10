
# TV Settings HAL Documentation




# Version and Version History


# History

| Date | Author | Comment | Version |
| --- | --------- | --- | --- |
| 16/11/22 | Aishwariya Bhaskar | First Release | 1.0.0 |

Version format to be defined. Proposal: Major.Minor.Doc 

# Description

TV Settings HAL a.k.a Controlsettings-hal is an abstract layer, which will provide API to Modify/Control the Picture quality parameters, dimming modes, auto backlight modes.

![TV Settings HAL diagram](tv_settings_hal_architecture.png)

TvSettings-hal Initialize the HAL API's with pqmodes for specific platforms and Initiates communication with aml-pqclient.
Mainly TvSettings-hal API's are used to control the pqparams.

# Acrnoyms

1. HAL - Hardware Abstraction layer
2. SOC - System on chip 
3. CPU - Central Processing Unit

### Definitions

1.`Soc Vendor` \- Definition to encompass multiple vendors

# Component Runtime Execution Requirements

SOC is responsible for handling the PQ settings at the end device as per the request from application via TV Settings hal.
RDK Middleware has to monitor the response continuosly from the drivers upon requesting a settings change in TV. Failure to meet these requirements will likely result in tvError_t messages.

## Initialization and Startup

TvSettings HAL API will be initialized by Tv Mgr-Plugin module. RDK-V middleware expected to have complete control over the life cycle over the TV Settings HAL module.
 TV Mgr plugin will first initialize by setting all the PQ parameters 
 1. Initialize the TV Settings hal using the function: tvInit (int *) before configuring any parameters using get/set functions. 
 2. The TV settings hal will set all the PQ parameters for different content format and picture modes from the tvsettings.ini file as part of initialization. allmodes.conf decides the supported formats,pic modes, dimming modes, resolution etc.,
 3. We can then configure the PQ parameters such as Brightness, Contrast, Hue, ColorTemp, RGB Gain values etc., for different PQ modes using the get/set functions.
 4. We can also reset the parameters to the default value(set by config file) using the reset functions.
 5. Once the required PQ params are configured, we can terminate the tv hal instace using tvTerm().

Need to call the function sequence in above order so that the system behaves
in a deterministic manner, every time.

## Threading Model

There is no requirement for the interface to be thread safe.

## Process Model

TVMgr-plugin will take care of Initializing TV Settings HAL component. At any point of time a single instance of TVMgr will exist to respond to any requests to configure the PQ parameters from application.

## Memory Model

The TV settings HAL is handling the pointers in heap memory for each of the parameters to be set/get. 
For asynchronous updates, HAL will pass message buffer in the callback and client is responsible to copy to its internal buffer before callback is returned.

## Power Management Requirements

TV Settings HAL does participate in power management., It will cooperate with the PQ Video Drivers for adjusting the PQ settings according to the power mode set.

## Asynchronous Notification Model

Change in Data update can be done asynchronously with the following API’s.
  1. For Updating Video Format change, use this function: RegisterVideoFormatChangeCB(tvVideoFormatCallbackData& cbData)

  2. For updating the Video Resolution change, use this function : RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData& cbData)

  3.  For updating the video Frame Rate, use this function: RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData& cbData)


## Blocking calls

There are no blocking calls in TV settings hal

## Internal Error Handling

All the TV Settings HAL API should return error synchronously as a return argument from any of the types. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

TV Settings HAL will initialize the HAL with the parameters present in GENERIC_MODE_CONFIG_FILE(tvsettings.ini) .

The default PQ parameters are kept as a persistent data to set during initialization.
Every OEM vendor has to define the tvsettings.ini and allmodes.conf in OEM layer.

# Nonfunctional requirements

Following non functional requirement should be supported by the TV Settings HAL component.

## Logging and debugging requirements

TV Settings HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure TV Settings HAL is not contributing more to memory and CPU utilization while handling different scenarios of PQ settings.

## Quality Control

There should not be any memory leaks/corruption introduced by HAL and underneath SOC software. TVSettings HAL should pass coverity scan verification without any issue.

## Licensing

TV Settings HAL implementation is expected to get released under the Apache License. 

## Build Requirements

TV Settings HAL source code should be build under Linux Yocto environment and should be delivered as a shared library.
  
## Variability Management

Any new API introduced should be implemented by all SOC vendor and RDK generic code will be compatible with specific version of TV Settings HAL software.

## Platform or Product Customization

Product or platform specific requirements can be handled in TV settings HAL API and the Specifications for respective product can be modified in config file.

# Interface API Documentation

Using below mentioned steps  Doxygen documentation can be generated
1. Run generate_docs.sh located at rdk-components-hal-tvsettings/docs
2. Go to rdk-components-hal-tvsettings/docs/output/html
3. index.html will show the documentation

## Theory of operation and key concepts

The TV settings HAL acts as interface between the TV Mgr Plugin and PQ drivers for handling various functionalities related to PQ settings such as Brightness, Contrast, Hue, Saturation, Luminence, White Balance, Sharpness, Color Temperature, Backlight, Aspect Ratio etc., 
When the User wants to change the above settings with remote, The request is first sent to AS and it navigates it as a curl request to TV manager Thunder plugin which then extracts the response and sends to TV Settings HAL.
This HAL will then sends the corresponding request to PQ driver and do the necessary operation.

### UML Diagrams

#### Sequence Diagram

![TV Settings HAL Init Sequence diagram](InitSequence.png)
![TV Settings HAL Set Sequence diagram](SetSequence.png)
![TV Settings HAL Get Sequence diagram](GetSequence.png)
![TV Settings HAL Reset Sequence diagram](ResetSequence.png)

#### State Diagram

![TV Settings HAL State Diagram](state_diagram.png)
