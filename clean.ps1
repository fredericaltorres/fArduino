gci -path . -rec -include compile.*.xml | remove-item                 
gci -path . -rec -include configuration.*.xml     | remove-item                 
gci -path . -rec -include upload.*.xml     | remove-item                 
gci -path . -rec -include *.vsarduino.h | remove-item  
gci -path . -rec -include *.sdf | remove-item  
gci -path . -rec -include *.lastbuildstate | remove-item  
