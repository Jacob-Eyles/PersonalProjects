%This function will create an 'actionshot' image that by finding the pixels
%from a stack of images (within a cell array) which are the most 'distant'
%from the median red, green and blue values. Each new pixel in the new
%image is the most distant when comapring each corresponding pixels within
%the set of source images.

%The input is a 1 by n cell array (where n denotes the number of source
%images) and the output is the action removed image as a 3D array.

% Author: Jacob Eyles

function [actionImage] = ActionShot(picarray)

%Taking the size and length of each image 3D array within the 'picarray'
%cell array.
[row,col,~] = size(picarray{1});
Length = length(picarray);

%Pre-allocating 4 dimensional matrices for Red,blue and green arrays. These
%4d arrays will be filled with all the r,g,b values of all the values from
%each of the 3d arrays in the 'picarray' cell array.
Red=zeros(row,col,3,Length);
Blue=Red;
Green=Red;

for i=1:Length
    
    %Each layer of the 4d array will be values of corresponding 3d array
    %in the'picarray'. Within each 4d layer will be the three layers for
    %the r,g,b values of that particular image (within the 'picarray').
    Red(:,:,1,i) = picarray{i}(:,:,1);
    Green(:,:,2,i) = picarray{i}(:,:,2);
    Blue(:,:,3,i) = picarray{i}(:,:,3);
    
end

%The median of all of the first red layer across every image (every 4d
%layer) is placed in the medianRed array. The same is produced for the
%green and blue values (in the medianGreen and MedianBlue arrays).
medianRed= median(Red(:,:,1,:),4);
medianGreen= median(Green(:,:,2,:),4);
medianBlue= median(Blue(:,:,3,:),4);

%The actionRemoved array is pre-allocated to have the original dimensions
%of the images in 'picarray'.
actionRemoved = zeros(row,col,3);

%The median red,green and blue arrays are placed in the 3d array layers
%1,2,3 respectively of the actionRemoved array.
actionRemoved(:,:,1) = medianRed;
actionRemoved(:,:,2) = medianGreen;
actionRemoved(:,:,3) = medianBlue;

%The actionRemoved image contains the median values for all the r,g,b
%values across all the images.

%creating a preallocated array for the sqauredistance values.
squareDistance = zeros(row,col,Length);

%for each image being processed, the pixeldistance2 function calculates the
%pixel distance for a whole array. A 3d array of these 'layers' of
%distances is produced.
for num = 1:Length
    squareDistance(:,:,num) = PixelDistance2(actionRemoved,picarray{num});
end

%The maximum distance across the layers for each pixel position is indexed
%as a 3d layer. So each entry will be what layer (image) the largest
%distance occurs. The linear function produces a linear index for each
%square distance pixel so this can help to identify which layer or image it
%is in.
[~,Index] = max(squareDistance,[],3,'linear');

%A 4d array is created that accomodates for the images in 'picarray' to be
%concantenated together in the 4th dimension.
array = zeros(row,col,3,Length);
array(:,:,:,:)=cat(4,picarray{:});

%An empty array is created for the actionImage.
actionImage = zeros(row,col,3);

%The loop sorts the index values in layers of pixels. Layer 1 occurs if
%any of the linear index are below the index of (row*col). Any larger and
%this will be in the next layer (2). If the condition is true, a 1 will
%appear in that pixel position. The actionImage is filled up. The first
%image in the 4D array is multplied by the layer 1 of 'ones' so only those
%3D pixels are placed in the action Image. All the rest are set to zero.
%The loop continues until there are no more layers(images). The similar
%process occurs for each layer as they are multiplied by the 4D array and
%added  to action Image. These are all different values to the previous
%layer(s) so will add fine.

for i=1:Length
    
    %Checking the values in layer 'i' into an array of ones and zeros.
    Layer = (Index>((i-1)*row*col) & Index<=(i*row*col));
    
    %This array is multiplied by the 4D image array corresponding to
    %the ith image and added to the action Image array. Each
    %multiplication gathers a 3D pixel to be added to the action image,
    %so eventually the action Image will be a complete 3D array.
    actionImage(:,:,:) = actionImage + array(:,:,:,i).*Layer;
    
end

%The double values must be converted to uint8 values to be processed as an
%image.
actionImage = uint8(actionImage);

end





