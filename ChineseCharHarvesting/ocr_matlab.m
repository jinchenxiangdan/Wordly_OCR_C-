function [text, words, confidence] = ocr_matlab(image_matlab)
% function [text, words, confidence] = ocr_matlab(image_matlab)
% 
% Use ocr to recogenize an image and return information that the OCR get.
%
result = ocr(image_matlab,'Language','ChineseTraditional','TextLayout','Word');
% output
text = result.Text;
words = result.Words;
confidence = result.CharacterConfidences;
end
