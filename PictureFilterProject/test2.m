[row,col,~] = size(picarray{1});
Length = length(picarray);


Red=zeros(row,col,3,Length);
Blue=Red;
Green=Red;

for i=1:Length
    
    Red(:,:,1,i) = picarray{i}(:,:,1);
    Green(:,:,2,i) = picarray{i}(:,:,2);
    Blue(:,:,3,i) = picarray{i}(:,:,3);
    
end


medianRed= median(Red(:,:,1,:),4);
medianGreen= median(Green(:,:,2,:),4);
medianBlue= median(Blue(:,:,3,:),4);

actionRemoved = zeros(row,col,3);

actionRemoved(:,:,1) = medianRed;
actionRemoved(:,:,2) = medianGreen;
actionRemoved(:,:,3) = medianBlue;

actionRemoved = uint8(actionRemoved);



squareDistance = zeros(row,col,Length);

for num = 1:Length
    squareDistance(:,:,num) = PixelDistance2(actionRemoved,picarray{num});
end

[~,Index] = max(squareDistance,[],3);

actionImage = zeros(row,col,3);
% pixels = Index;
% pixels(:,:) = arrayfun(IndexPixel,Index);
pixels(:,:) = picarray.{

for i=1:row
    for j=1:col
        actionImage(i,j,:) = picarray{Index(i,j)}(i,j,:);
    end
end

actionImage = uint8(actionImage);

