
# The name of our repository is eagles/optimus/2012

# cloning our repo to your own local repo for the first time:
cd /cygdrive/c/Users/$USER/Desktop
mv eagles OLD_EAGLES
mkdir -p eagles/optimus
cd eagles/optimus
git clone ssh://git@gir.garagerobotics.com:2222/eagles/optimus/2012
cd 2012

# after making changes and commiting them locally:
git push




# examples of adding files, making changes and then pushing them
# back to the main repo:

git clone git@gir:eagles/optimus/2012
cd 2012/
mkdir RobotC
cd RobotC/
vi armKinetics.c
cd ..
git add RobotC/armKinetics.c 
git commit -m "first file"
git push -u origin master
-after the very first push to a new repo, a simple git push will work
git push

