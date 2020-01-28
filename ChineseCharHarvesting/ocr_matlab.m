function [text,words] = ocr_matlab(image_matlab)

result = ocr(image_matlab,'Language','ChineseTraditional','TextLayout','Word');


text = result.Text;
words = result.Words;
end
