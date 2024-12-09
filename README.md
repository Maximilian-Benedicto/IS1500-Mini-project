# DTEK Project – 3d rendering!

## How to run
* Configure the DTEK-V toolchain provided by the course IS1500.
* Enter directory ```~/DTEK-project-24/src```.
* Enter command ```make```.
* Connect the card to the computer.
* Connect the card to a VGA supported display.
* Run by writing the command ```dtekv-run main.bin```.

### Note
If the code is not being transfered properly run the commands ```killall jtagd``` and subsequently ```jtagd --user-start```.

## IO

The switches and buttons on the card can be used to control the simulation. See below for instructions:
| IO      | Action                          |
|---------|---------------------------------|
| sw0     | Move scene down                 |
| sw1     | Move scene up                   |
| sw2     | Rotate scene right              |
| sw3     | Rotate scene left               |
| sw4     | Rotate scene down               |
| sw5     | Rotate scene up                 |
| sw6     | Move scene away                 |
| sw7     | Move scene closer               |
| sw8     | Wireframe enable                |
| sw9     | Z-buffer enable                 |
| btn0    | Stop simulation                 |
| led0-9  | Indicate which switches are enabled |

## Authors
Arman Montazeri
Maximilian Benedicto
