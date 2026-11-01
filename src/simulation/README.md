# Simulation application example


## Build (compile and link)

In `stm-sandbox/src/simulation/`:

    $ make build


## Run

    $ make run

The application opens a simple console which accepts the following inputs:
* `power on`: emulates a telecommand (TC) to power on the payload
* `power of`: payload power off TC
* `status on`: emulates power status notification on from the ADC
* `status off`: emulates power status notification off from the ADC

Three files are generated:
* `mock.out`: commands sent to the actuator (an example of simple "fake" or "stub")
* `obc.out`: report on power on/off commands
* `adc.out`: report on power status notifications from ADC

Every record in these files contains additonally time referece (10Hz time-stamp from OBC task).

You can follow the changes of the files with, e.g., `tail -F mock.out`, preferably in a separate terminal window.

In three separate terminal windows:

	$ tail -F mock.out
	$ tail -F obc.out
	$ tail -F adc.out

## Debug

	$ gdb ../../build/sandbox-sim/scons-release/src/sandbox-sim.elf
