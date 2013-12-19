import numpy as np
import matplotlib.pyplot as plt
import os 
import linecache


# try:
data = np.genfromtxt("10Ktest_watercombined.txt")
nbinsX = int(linecache.getline("histheader.txt", 1))
nbinsY = int(linecache.getline("histheader.txt", 2))
minX = float(linecache.getline("histheader.txt", 3).split()[0])
maxX = float(linecache.getline("histheader.txt", 3).split()[1])
maxY = float(linecache.getline("histheader.txt", 4).split()[0])
minY = float(linecache.getline("histheader.txt", 4).split()[1])
print(nbinsX, nbinsY, minX, maxX, minY, maxY)
# except:
# 	#must've already combined them...
# 	data = np.genfromtxt("combined.txt")
# for result in os.listdir(os.getcwd()):
# 	if not (result.startswith("testhist")):
# 		temp = np.genfromtxt(result)
# 	try:
# 		data += temp
# # 		os.remove(result)
# 	except:
# 		print("Bad file found: %s\nIt has been deleted..."%result)
# # 		os.remove(result)
# 	
# 
# np.savetxt("combined.txt", data)


#data = np.genfromtxt("output/histotest_10K_water0")
print(data.shape)
plt.imshow(data, extent=[minX, maxX, maxY, minY])
plt.show()