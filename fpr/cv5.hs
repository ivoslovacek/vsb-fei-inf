import Data.Char

oddList :: Int -> Int ->  [Int]
oddList a b = [x | x<-[a..b], odd x]

removeAllUpper:: String -> String
removeAllUpper xd = [x | x<-xd, not (isUpper x)]

union :: Eq a => [a] -> [a] -> [a]
union xs ys = xs ++ [y | y<-ys, not(elem y xs)]
