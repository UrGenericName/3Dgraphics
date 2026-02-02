# converts given OBJ file into code that can be used in graphics library
# OBJ FILE MUST BE TRIANGULATED

directory = input("Directory to OBJ file (must be triangulated!): ");
obj = open(directory, "r");

# Iterate until get to vertices
line = obj.readline();
while(line[0] != 'v'):
    line = obj.readline();

# Push all verticies into vector
vertices = [];
while(line[0] == 'v' and line[1] == ' '):
   
    x = "";
    i = 2;
    while(line[i] != " "):
        x += line[i];
        i += 1;
    
    y = "";
    i += 1;
    while(line[i] != " "):
        y += line[i];
        i += 1;
    
    z = "";
    i += 1;
    while(line[i] != "\n"):
        z += line[i];
        i += 1;

    vertices.append([float(x), float(y), float(z)]);
    line = obj.readline();

# Iterates down the file until it reaches the face definitions
while (line[0] != 'f'):
    line = obj.readline();

# For each face, construct the polygon function call as a string and print
convertedOBJ = "";
while(line != '' and line[0] == 'f'):
   
    pointA = "";
    i = 2;
    while(line[i] != "/"):
        pointA += line[i];
        i += 1;
    
    while(line[i] != " "):  # skip to next point
        i += 1;

    pointB = "";
    i += 1;
    while(line[i] != "/"):
        pointB += line[i];
        i += 1;
    
    while(line[i] != " "):  # skip to next point
        i += 1;

    pointC = "";
    i += 1;
    while(line[i] != "/"):
        pointC += line[i];
        i += 1;

    pointA = vertices[int(pointA) - 1];
    pointB = vertices[int(pointB) - 1];
    pointC = vertices[int(pointC) - 1];

    pointAstr = str(pointA[0]) + 'f, ' + str(pointA[1]) + 'f, ' + str(pointA[2]) + 'f';
    pointBstr = str(pointB[0]) + 'f, ' + str(pointB[1]) + 'f, ' + str(pointB[2]) + 'f';
    pointCstr = str(pointC[0]) + 'f, ' + str(pointC[1]) + 'f, ' + str(pointC[2]) + 'f';

    # print the function call
    functionCall = "Polygon{ Point(" + pointAstr + "), Point(" + pointBstr + "), Point(" + pointCstr + ") },"
    convertedOBJ += functionCall + '\n';

    line = obj.readline();

convertedOBJ = convertedOBJ[:-2];   # edge case to remove comma and \n
print(convertedOBJ);