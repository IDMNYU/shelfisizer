# shelfisizer
Open-source modular synthesizer designs. Developed at the BxmC at NYU IDM.

The Shelfisizer is an open-source project by Luke DuBois inspired by Serge modular systems but also hybrid analog synthesis / microcontroller systems such as the Buchla 200e. These modules use 16mHz Adafruit Metro Mini microcontrollers and simple monolithic IC chips to handle much of the logic that definies the module’s behavior, leaving discrete components for the parts of the modules that actually generate analog signals. The use of microcontrollers makes it simple to prototype modules that require an understanding of “state”, such as pattern memory or hysteresis, and the use of CMOS ICs allows for a design that has a much lower part count than typical analog synthesizer modules.
