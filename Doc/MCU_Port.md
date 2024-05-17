# How to port this project for different RA Evaluation kits (EK)

- Import the Application software (`app` folder)
- Up the Main Stack size to `0x1000` in `FSP Configuration` >> `BSP` (tab) >> `Properties` >> `RA Common` >> `Main Stack size (bytes)`
- Add some Heap (e.g. `0x100`) in `Heap size (bytes)`
- Setup UART pins connected to the PMOD2 connector (see the evaluation kit user's manual or schematics)
