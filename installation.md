# EmbedPy, Pandas, Pyarrow setup
## enter below commands in order
### to install conda:
 wget https://<span></span>repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda.sh
 
 bash ~/miniconda.sh -b -p ~/miniconda 
 
 ` rm ~/miniconda.sh `
 
 export PATH=~/miniconda/bin:$PATH 
### create kdb conda environment:
conda create --name kdb python=3.7.3

conda activate kdb
conda install -c kx embedPy
conda install pandas
conda install pyarrow
 
 
 ### to restore to normal environment:
 conda deactivate
