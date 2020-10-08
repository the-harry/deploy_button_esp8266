# Deploy Button ESP8266

## ABOUT

This project was created to be an generic and agnostic environment deploy button, it can deploy to multiple servers(16 limit) in different build conditions, that also may handle different languages in the same device.

The trick here is to delegate all the complexity of the environments to an API running on your local machine, so the device itself only need to build a request based upon your choises and the API will handle it by matching a ENV that has the command to deploy in the environment that you have chose when the button was triggered. And how probably you already have those dependencies and accesses in your machine it wont be concern at all.


## GETTING STARTED

## SOFTWARE

All the device code is in `device.ino`, before uploading the code to the device, remember to change wifi `SSID` and `PASSWORD` so the device can make a post to the API when you hit the button.

Also change the `API_KEY` to something safe, I recomend using a password generator for that.

After uploading the code it will blink both leds while it is not connected to wifi, when a deploy is triggered if the API returns 201 for the request it will blink the green led, if some error happen and the API returns 500 the device will blink the red one.

## HARDWARE

To build this project you will need the following itens, some of then are optional:

* ESP8266

* Jumpers

* 1 Red Led

* 1 Green Led

* 2 220ohm resistors

* 1 DIP SWITCH 4 terminals

* 1 Pushbutton module (You could also use a Pushbutton with a 220ohm resistor)

* 1 Mechanical switch and keycap (I've used a cherry MX blue) - (Optional, you may use only the push button, though it wont be so coll)

* 1 box (You can use any box that are able to fit all components, wood or plastic would be my choise, I've used an old ABS plastic box out of a power unit of an old printer, after some cuts and tweeks it was good to go)

* Hotglue and some thermo-retractile tubes is also good to have but may be replaced.


If you want to add a safety lock mechanism like I did you will need the following parts: (But you can build without it as well, just be aware that any acidental hit in the button may trigger a deploy)

* 1 Tubular lock (I've used one F&K Technologies Notebook lock that I had laing arround but you can use other model)

* 1 key ring (It will be flattened and glued to the end of the lock, so when it is rotated the circuit is closed)

* 2 medium nails

* 1 piece of wood (4CM X 2CM)

* Ducktape or glue to hold the wood inside the box


## ASSEMBLE


## PINOUT
