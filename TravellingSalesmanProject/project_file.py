# ---------------------------------------------
# IMPORT LIBRARIES:
# ---------------------------------------------
from project_utils import *
import networkx as nx
from multiprocessing import Pool
import numpy as np
import time

# ---------------------------------------------
# FUNCTIONS:
# ---------------------------------------------

def closest_node(network, source, destinations):
    ''' Find the closest node in a set of detinations to a given source in a network.
	
		Parameters
		----------
		network : networkx graph
			Derivative function.
		source : string
			Name of the source node.
		destinatins : list
			List of all destinations to compare to source.

		Returns
		-------
		node : string
			Name of closest node in destinations.
		minimum : float
			distance from source to closest node. 

    '''
    # remove the source if part of the destinations list.
    if source in destinations:
        destinations.remove(source)
    # initialise array for distances from source for destinations.
    distances = []

    # for every destination find the length of the shortest path from the source.
    for place in destinations:
        distances.append(nx.shortest_path_length(network, source = source, target = place, weight = 'weight'))
    # the minimum path length is the closest node.
    minimum = np.min(distances)
    node = destinations[np.where(distances == minimum)[0][0]]
    # return the closest node from the destination set and the minimum path length.
    return node, minimum

def nearest_neighbour(network, source, destinations):
    ''' Use a greedy algorithm to define a path from a source to a destination 
        in a network.
	
		Parameters
		----------
		network : networkx graph
			network to search.
		source : string
			Name of the source node.
		destinatins : list
			List of all destinations (as strings) to compare to source.
			
		Returns
		-------
		path : list
			chronological list of all nodes visited in a path from source to 
            all other sepcified destinations in a network.  
		total : float
			total distance taken on path.
			
		Notes
		-----
		Destination nodes must be part of the network.
        The algorithm Only stops once all nodes in the destination list have been visited.
    '''
    path = []   # path of all destinations using greedy algorithm.
    # the path will not contain the source node.
    total = 0   # total distance covered.

    while True:
        # The nearest node to the (current) source is found.
        neighbour, dist = closest_node(network, source, destinations)
        # this closest node is defined as 'visited' so is removed from the destinations,
        # and added to the path.
        destinations.remove(neighbour)
        path.append(neighbour)
        total += dist
        # The node was was most recently visited is now the new source node.
        source = neighbour

        # The loop ends when all the destinations have been reached. The path list and the 
        # total distance are returned.
        if destinations == []:
            return path,total
    
def latcut(network, homes, latsplit = None):
    ''' Seperate a subset of a network by latitude.
	
		Parameters
		----------
		network : networkx graph
			network to search.
		homes : list
			subset of overall network.
		latsplit : float
			latitude to seperate the network subset.
			
		Returns
		-------
		North : list
			list of all home nodes above the latitude split.
		South : list
			list of all home nodes below the latitude split.
			
		Notes
		-----
		If no input for latsplit, the average of all home 
        latitudes in the homes subset is used. 
    '''
    latitudes = []  
    North = []
    South = []

    # collect the latitudes of all nodes in the homes list.
    for home in homes:
        latitudes.append(network.nodes[home]['lat'])
    # If a latitude to split at has not been defined, use the median of all node latitudes.
    if latsplit == None:
        latsplit = np.median(latitudes)
    # loop through all the latitudes and compare to the latitude split.
    for i in range(0,len(homes)):
        # if the latitude is larger than the split, the corresponding home is place in a list North.
        if latitudes[i] > latsplit:
            North.append(homes[i])
        # the opposite for South
        else:
            South.append(homes[i])
    
    return North,South

def lngcut(network, homes, lngsplit = None):
    '''Seperate a subset of a network by longitude.
	
		Parameters
		----------
		network : networkx graph
			network to search.
		homes : list
			subset of overall network.
		lngsplit : float
			longitude to seperate the network subset.
			
		Returns
		-------
		West : list
			list of all home nodes left the longitude split.
		East : list
			list of all home nodes right the longitude split.
			
		Notes
		-----
		If no input for lngsplit, the average of all home 
        longitudes in the homes subset is used. 
    '''
    longitudes = []
    West = []
    East = []
    # gather longitudes for all nodes in homes.
    for home in homes:
        longitudes.append(network.nodes[home]['lng'])

    # if not defined, the lngsplit will be the average of the longitudes.
    if lngsplit == None:
        lngsplit = np.median(longitudes)

    # arrange the homes into graoups east and west of the lngsplit. 
    for i in range(0,len(homes)):
        if longitudes[i] > lngsplit:
            East.append(homes[i])
        else:
            West.append(homes[i])
    
    return West,East

def cut(network, homes, inputs):
    '''Cuts up a network into smaller subsets. A path for each subset
        visiting all subset nodes is created. 
	
		Parameters
		----------
		network : networkx graph
			network to search.
		homes : list
			List of all destinations (as strings) to map.
        inputs : list
			List of inputs to cut up each network subset.
			
		Returns
		-------
		allpaths : array-like
			a set of paths through the subsets which correspond to the 
            'inputs' into the function.
		alldistances : array - like
			list of total distance taken on different paths through various subsets.
			
		Notes
		-----
		inputs must be of this template:
        inputs = [ Courier number, Longitude cut, West Latitude cut, East Latitude cut, order of quandrants]
        -The courier number dictates the subset to map
        -The Longitude cut is the longitude split of the subset
        -West/East Latitude cut relates to the latitude split of the East and West regions of the subset.
        -Order of quadrants is the order in which to map the subset overall.
            eg: [0,1,2,3] maps SB,NB,NA,SA in order for the subset path.
        quadrants are defined as below:
        ------------------
        |   NA  |   NB   |
        |  (2)  |  (1)   |
        ------------------
        |   SA  |   SB   |
        |  (3)  |  (0)   |
        ------------------
        The number of path in allpaths corresponds to the number of lists in 'inputs'.
    '''
    
    alldistances = []
    allpaths = []

    # The first cut seperates the first courier homes to the north of the Harbour Bridge.
    courier1,courier234 = latcut(network, homes, latsplit= -36.832)
    # The one home which is a large distance from the rest of courier1 homes is removed and added to 
    # the other courier routes "Radius Taupaki Gables".
    courier234.append('Radius Taupaki Gables')
    courier1.remove('Radius Taupaki Gables')
    # The remaining homes are split to seperate courier 2 and part of courier3's path to the West and 
    # part of couriers 1 and 3 and 4 to the East.
    courier23,courier134 = lngcut(network, courier234, lngsplit = 174.768)
    # The section on the West is cut again to contain only courier 2 to the West and part of courier 3 to the East.
    # The "Radius Taupaki Gables" is now part of courier 2 path.
    courier2,courier3extra = lngcut(network, courier23, lngsplit = 174.68)

    # collect a group of homes by the bridge, which are logical to add to the path of courier1.
    Bridgehomes = ['Jervois Residential Care', "St Joseph's Home & Hospital", "Lynton Lodge Hospital","St Catherine's Rest Home"]
    # remove these from the part of courier3.
    courier3extra = [home for home in courier3extra if home not in Bridgehomes]

    # split the other group containg parts of couriers 1, 3, 4. This makes the part of couier 1 
    # contain homes on a pathway towards the bridge which is logical.
    courier1extra,courier34 = lngcut(network, courier134, lngsplit = 174.781)
    # for efficiency, the extra courier 1 homes are split north and south of a latitude to streamline the greedy algorithm
    courier1extratop, courier1extrabot = latcut(network, courier1extra, latsplit= -36.885)

    # The remaining homes are split so the southern homes all belong to courier4.
    courier34extra,courier4 = latcut(network, courier34, latsplit= -36.91)
    # An extra portion out East is added to courier4 path.
    courier3,courier4extra = lngcut(network, courier34extra, lngsplit = 174.8755)
    courier4.extend(courier4extra)
    
    # The main courier paths are put into a list which is then run through according to the function 'inputs'.
    couriers = [courier1, courier2, courier3, courier4, courier3extra]
    # A seperate sub list of extra routes for courier 1 is made:
    routes1 = [courier1extrabot, courier1extratop,Bridgehomes]

    
    for inputs in inputs:
        # The source defualt should be auckland Airport
        source = ['Auckland Airport']
        path = []
        distance = 0

        # any sub routes added (such as for path1) will be added to a seperate route and distance.
        pathextra = []
        distanceextra = 0

        # The first inputs index denotes the courier number which is related to the couriers list above.
        # This is split by a longitude of inputs[1].
        A,B = lngcut(network, couriers[int(inputs[0]) - 1], lngsplit= inputs[1])

        # if the first courier path is being determined, 
        if inputs[0] == '1':
            # cycle through the 'extra routes' for courier1.
            for paths in routes1:
                # for each route, calculate the distance and path and add to extra total.
                pathx,distancex = nearest_neighbour(network,source[0],paths)
                pathextra.extend(pathx)
                distanceextra += distancex
                # The new source for the next path is the last home in the previous path.
                source = [pathx[-1]]
            
            # The extra path starts at the Airport.
            pathextra = ['Auckland Airport'] + pathextra
            # The last home is removed as this is the source for the main route.
            pathextra.pop(-1)


        if inputs[0] == '5':
            # '5' is the extra path for courier 3. This does not come back to the Airport 
            #  so has no destination.
            quadpath, quaddist = quadcut(network, source, A, B, inputs, destination = None)
        elif inputs[0] == '3':
            # The main route of courier 3 wont start at the airport but at the end of the 
            # extra part of courier 3. This is 'Edenvale Rest Home'.
            quadpath, quaddist = quadcut(network,['Edenvale Rest Home'],A, B, inputs)
        else:
            quadpath, quaddist = quadcut(network, source, A, B, inputs)

        # The total distance for that courier is added together and the path is extended.
        distance = distanceextra + quaddist
        path = pathextra + quadpath

        # Each courier path and distance is collated and returned as an ouput.
        alldistances.append(distance)
        allpaths.append(path)
    

    return allpaths, alldistances


def quadcut(network, source, A, B, inputs,  destination = 'Auckland Airport'):
    '''Cuts up a network subset. A path linking each subset visiting all subset 
        nodes is created. 
	
		Parameters
		----------
		network : networkx graph
			network to search.
		source : string
			start of path
        A : list
            subset of a network
        B : list
            subset of a network
        inputs : list
			List of inputs to cut up each network subset.
        destination : string
            final node visited in path.
			
		Returns
		-------
		path : array-like
			a paths through the all subsets.
		distance : float
			total distance taken on path through all subsets.
			
		Notes
		-----
		inputs must be of this template:
        inputs = [ Courier number, Longitude cut, West Latitude cut, East Latitude cut, order of quandrants]
        -The courier number dictates the subset to map (not used in this function)
        -The Longitude cut is the longitude split of the subset (used to create subsets A and B, not used in this function)
        -West/East Latitude cut relates to the latitude split of the East (B) and West (A) regions of the subset.
        -Order of quadrants is the order in which to map the subset overall.
            eg: [0,1,2,3] maps SB,NB,NA,SA in order for the subset path.
        quadrants are defined as below:
        ------------------
        |   NA  |   NB   |
        |  (2)  |  (1)   |
        ------------------
        |   SA  |   SB   |
        |  (3)  |  (0)   |
        ------------------
    '''
    # The path starts off at the source.
    path = source
    distance = 0

    # The two halves of the destinations are split by the inputs to the function. 
    NB,SB = latcut(network, B, latsplit= inputs[3])
    NA,SA = latcut(network, A, latsplit= inputs[2])

    # An array denotes the 4 quadrants of the courier route:
    array = [SB,NB,NA,SA]
    # ------------------
    # |   NA  |   NB   |
    # |  (2)  |  (1)   |
    # ------------------
    # |   SA  |   SB   |
    # |  (3)  |  (0)   |
    # ------------------
    # The index order in the inputs will dictate the order in which 
    # the quadrants are cycled through.
  
    for i in range(0,4):
        try:
            # for each quadrant, find the greedy path and distance.
            px,dx = nearest_neighbour(network,source[0],array[inputs[4][i]])
            # set the source to the last visited node of the last quadrant.
            source = [px[-1]]
        except:
            # if there are no homes in the quadrant, distance is 0 and the path is null.
            # The source is unchanged.
            dx = 0
            px = []
        
        # sum the paths and distances
        distance += dx
        path = path + px

    # Once all the quadrants are added to the main path, calculate the distance from the last visited home 
    # to the airport. If destination is 'None' dont add any more distance or path.
    if destination is not None:
        back = nx.shortest_path_length(network, source = path[-1], target = destination, weight = 'weight')
        distance += back
        path.append(destination)

    return path, distance


def write(allpaths, inputs):
    '''Write a .txt file containing all nodes along a path.
	
		Parameters
		----------
		allpaths : array-like
			lists of paths to write.
		inputs : list
			corresponding file name inputs for each path.
			
		Notes
		-----
		Each file created is of name "path_N.txt" where N is the string in the list 'inputs'.
        Every node written in the path files is on a new line.
        A seperate file is created for each path.
    '''
    j = 0
    for path in allpaths:
        
        # the file is named 'path_N.txt' where N is the courier number.
        fp = open('path_'+inputs[j]+'.txt', 'w')
        # every home in the path is written on a new line.
        for i in path:
            fp.write(i+'\n')

        fp.close()
        j += 1

def maproute(network,homepaths):
    '''Create a path through a network given a set of intermediate nodes to follow.
	
		Parameters
		----------
		network : networkx graph
			network to search.
		homepaths : list
			subset of network containing path of nodes.
			
		Returns
		-------
		maproutes : list
			list of all paths through the network.
			
		Notes
		-----
		A seperate path is created for each list entry in hompaths.
    '''
    maproutes = []
    # sort through each input path
    for path in homepaths:
        maproute = []
        # find path from two consecutive points in the path. 
        # Do this for all points which are consecutive in sequential order.
        for i in range(0,len(path)-1):
            addpath = nx.shortest_path(network, source = path[i], target = path[i+1], weight = 'weight')
            maproute.extend(addpath)

        maproutes.append(maproute)

    return maproutes

# ---------------------------------------------
# MAIN CODE:
# ---------------------------------------------

# read the network and obtain the list of rest homes.
auckland = read_network('network.graphml')
rest_homes = get_rest_homes('rest_homes.txt')

# define the input for every courier path:
# template: [ Courier number, Longitude cut, West Latitude cut, East Latitude cut, order of quandrants]

# quadrants are defined as below:
# ------------------
# |   NA  |   NB   |
# |  (2)  |  (1)   |
# ------------------
# |   SA  |   SB   |
# |  (3)  |  (0)   |
# ------------------

input1 = ['1',174.723,-36.76875,-36.76875,[0,1,2,3]]         # = 15.21
input2 = ['2',174.6208,-36.8777,-36.8777,[1,2,3,0]]          # = 15.177
input3 = ['3',174.87547,-36.9,-36.9,[2,1,0,3]]               # = 15.28
input4 = ['4',174.8742,-36.99,-36.99,[2,1,0,3]]              # = 15.13
input5 = ['5',174.722,-36.8945,-36.8945,[0,3,2,1]] 

# the inputs array is passed into the cut function.
inputs = [input1, input2, input3, input4, input5]

# start = time.time()

# the paths of all the couriers and the correpsonding distances are the ouput.
paths,distances = cut(auckland,rest_homes, inputs = inputs)

# end = time.time()
# print(end-start)

# the courier 3 path includes both inputs 3 (courier3) and 5 (courier3extra).
courier3 = paths[4]
# the destination of the extra part of courier3 is removed as this is the same 
# as the source of courier3.
courier3.pop(-1)
# the courier3 extra and courier3 are added together to make one path.
courier3.extend(paths[2])

# the list of final paths and the corresonding courier numbers are written into 
# seperate txt files.
courierpaths = [paths[0],paths[1],courier3,paths[3]]
couriernumbers = ['1','2','3','4']

write(courierpaths, couriernumbers)

# print(f'distance of c1 is: {distances[0]}')
# print(f'distance of c2 is: {distances[1]}')
# print(f'distance of c3 is: {distances[2] + distances[4]}')
# print(f'distance of c4 is: {distances[3]}')

# calculate the route path through the network.
courierroutes = maproute(auckland, courierpaths)

# plot_path(auckland, courierroutes[0], save = 'path_1.png')
# plot_path(auckland, courierroutes[1], save = 'path_2.png')
# plot_path(auckland, courierroutes[2], save = 'path_3.png')
# plot_path(auckland, courierroutes[3], save = 'path_4.png')



