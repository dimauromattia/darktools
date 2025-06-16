# MadDM

**MadDM** is a plugin for ``MG5_aMC@NLO`` (**MadGraph**) for the computation of several dark matter-related observables.

## Requirements

- MadGraph v2.9 (LTS version) is required to run the latest version of MadDM, MadGraph v3.* may be supported but more testing is necessary (**notice: this is not the same version used for the MadGraph tutorials**).
- Python 3.6+
- `gfortran`
- `make`
- `cmake`
- python package:
    - [`six`](https://pypi.org/project/six/): to support Python 2.7 as well
    - [`numpy`](https://numpy.org/)
    - [`scipy`](https://scipy.org/) (required for some recent features)

## Installation

There are two ways to install MadDM for the tutorial session:
- good old manual way (Linux, Mac, and Windows with *Windows Subsystem for Linux* - WSL);
- Docker image.

### Good old manual way

Given **MadDM** depends on **MadGraph**, we first need to install the latter, for example, for MadGraph v2.9.24, we need to:

1. Download the tarball from the [MadGraph5_aMC@NLO website](https://launchpad.net/mg5amcnlo):
   ```bash
   wget https://launchpad.net/mg5amcnlo/3.0/3.6.x/+download/MG5_aMC_v2.9.24.tar.gz
   tar xzf MG5_aMC_v2.9.24.tar.gz
   cd MG5_aMC_v2_9_24
   ```
2. Go into the directory `PLUGIN` and run the following command to clone the MadDM repository, and to copy the executable file:
   ```bash
   cd PLUGIN
   git clone -b dev --depth 1 --recurse-submodules --shallow-submodules https://github.com/maddmhep/maddm.git
   mv maddm/maddm ../bin/maddm.py 
   ```
3. Go back to the main directory and run MadDM with:
   ```bash
   cd ..
   ./bin/maddm.py
   ```
4. Install some prerequisites: [Pythia](https://pythia.org/) and the tabulated spectra [CosmiXs](https://github.com/ajueid/CosmiXs) (and [PPPC4DMID](http://www.marcocirelli.net/PPPC4DMID.html)):
   ```
   MadDM>install pythia8
   MadDM>install PPPC4DMID
   ```
   The installation of Pythia 8 will take care of automatically installing also [LHAPDF](https://www.lhapdf.org/index.html), `zlib` and the interface in between MadGraph and Pythia (`mg5amc_py8_interface`), while the command `install PPPC4DMID` will also install CosmiXs.
5. We need few BSM models, that you can download with the following commands, and place them in the `models/` folder in the main MadGraph directory:
   ```bash
   wget https://raw.githubusercontent.com/dimauromattia/darktools/refs/heads/main/maddm/DMsimp_s_spin1_MD.tar.gz
   tar xf DMsimp_s_spin1_MD.tar.gz -C models
   wget https://raw.githubusercontent.com/dimauromattia/darktools/refs/heads/main/maddm/ScalarHiggsPortal_NLO_UFO.tar.gz
   tar xf ScalarHiggsPortal_NLO_UFO.tar.gz -C models
   ```
6. You are now set, have fun!

This process may require around 20 min or more depending on the processing power of your computer.

### Docker image

We prepared a Docker image of around 2 GB, containing all the necessary things to run MadDM immediately.
This process is very fast, and depends mostly on the downloading speed to download the Docker image.

One needs to:
1. Install and setup Docker: Docker is available in most Linux distributions (use your package manager, see the [official docs](https://docs.docker.com/engine/install/), you can use this guide also for Windows with WSL), e.g. for Debian-based distributions:
   ```bash
   sudo apt install docker
   ```
   while for Mac, see the [official docs](https://docs.docker.com/desktop/setup/install/mac-install/).
   It is possible to setup Docker for Windows as well (without WSL), see the [official docs](https://docs.docker.com/desktop/setup/install/windows-install/).
   **Note**: you may need to use `sudo` to run Docker commands on the shell, unless you properly setup Docker to avoid using `sudo` (but if it is ok for you, just use `sudo`).
2. Download the image `maddm-3.3rc1.tar` from this [CERNbox link](https://cernbox.cern.ch/s/820EB77W5l80Vbj).
3. Load the image into Docker with the command:
   ```bash
   docker load --input maddm-3.3rc1.tar
   ```
   Remember that *you may need to use `sudo`*.
4. Now you can create and run a container based on the `maddm:3.3rc1` image with the following commands:
     - on Linux, Windows with WSL, and Mac **without Apple Silicon** (if your Mac is **not** one of the kind with the M\* processor):
       ```bash
       docker run -it --rm maddm:3.3rc1 /bin/bash
       ```
     - on Mac **with Apple Silicon** (if your Mac is of the kind with the M\* processor).
       ```bash
       docker run --platform linux/amd64 -it --rm maddm:3.3rc1 /bin/bash
       ```
     - on Windows without WSL using the Docker desktop graphics interface, create a container using the instructions for Docker desktop.

   Given we are using `--rm` option, the container will be stopped and eliminated once it is closed, so anything done while inside there will be lost.
   Remove the `--rm` option if you wish to keep the container active even after it has been closed.

   Notice that some commands like `display diagrams` may not work, and so far I made it working on Linux using the following command to spawn the container:
   ```bash
   docker run -it --rm \
       -v "/tmp/.X11-unix:/tmp/.X11-unix" \
       -e "DISPLAY=$DISPLAY" \
       maddm:3.3rc1 /bin/bash

5. You are now set, have fun!
