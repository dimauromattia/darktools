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
