
function [actionRemoved] = RemoveAction(picarray)

[row,col,~] = size(picarray{1});
Red=zeros(row,col,3,Length);
Blue=Red;
Green=Red;

for i=1:Length
    
    Red(:,:,1,i) = picarray{i}(:,:,1);
    Blue(:,:,2,i) = picarray{i}(:,:,2);
    Green(:,:,3,i) = picarray{i}(:,:,3);
    
end

medianRed= median(Red(:,:,1,:),4);
medianBlue= median(Blue(:,:,2,:),4);
medianGreen= median(Green(:,:,3,:),4);

actionRemoved = zeros(row,col,3);

actionRemoved(:,:,1) = medianRed;
actionRemoved(:,:,2) = medianBlue;
actionRemoved(:,:,3) = medianGreen;

actionRemoved = uint8(actionRemoved);
image(actionRemoved);

end
