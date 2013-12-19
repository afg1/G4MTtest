import numpy as np
import os

files = os.listdir(os.getcwd())

data = np.genfromtxt(files[0])
for result in files[1:]:
    temp = np.genfromtxt(result)
    try:
        data += temp
# 		os.remove(result)
    except:
        print("Bad file found: %s\nIt has been deleted..."%result)
# 		os.remove(result)

#except:
#    data = np.genfromtxt(files[1])
#    for result in files[2:]:
#        temp = np.genfromtxt(result)
#	try:
#		data += temp
## 		os.remove(result)
#	except:
#		print("Bad file found: %s\nIt has been deleted..."%result)
## 		os.remove(result)
#
#
np.savetxt("%scombined.txt"%(files[-1][:-1]), data)


#data = np.genfromtxt("output/histotest_10K_water0")
print(data.shape)