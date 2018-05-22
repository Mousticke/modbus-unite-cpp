# Simple modbus in cpp

### How to build the project
To execute the available script, please make build.sh executable
```chmod ugo+x build.sh```

Then you have to set a repository for the commit and push in your git
`./build.sh -init`
Enter the url of the repository and the name of the remote branch

### Arguments
- `-make_commit` : Execute the command make, do some clean up and commit
- `-make` : Execute the command make, do some clean up
- `-commit` : Do the commit
- `-push` : Push your branch