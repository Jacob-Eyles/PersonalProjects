% function [FinalIndex] = IndexPixel(picarray,Index,row,col )
% 
% [r,c]= size(Index);
% FinalIndex = zeros(r,c,3); 
% FinalIndex(row,col,:) = picarray{Index(row,col)}(row,col,:);
% 
% end
A=[1,4,6,8]
b=arrayfun(@(x)x*2,A)