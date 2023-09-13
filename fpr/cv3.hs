myFunction :: [a] -> [a]
myFunction [] = []
myFunction [x] = [x]
myFunction (x1 : x2 : xs) = x1 : myFunction xs

length' :: [a] -> Int
length' [] = 0
length' [x] = 1
length' (x : xs) = 1 + length' xs

sumIt :: [Int] -> Int
sumIt [] = 0
sumIt (x : xs) = x + sumIt xs

getHead :: [a] -> a
getHead [] = error "empty list"
getHead (x : _) = x

getLast :: [a] -> a
getLast [] = error "empty list"
getLast [x] = x
getLast (_ : xs) = getLast xs

getTail :: [a] -> [a]
getTail [] = []
getTail (_ : xs) = xs

getInit :: [a] -> [a]
getInit [] = []
getInit [x] = []
getInit (x : xs) = x : getInit xs

combine :: [a] -> [a] -> [a]
combine [] y = y
combine (x : xs) y = x : combine xs y

scalar :: [Int] -> [Int] -> Int
scalar [] [] = 0
scalar _ [] = 0
scalar [] _ = 0
scalar (x : xs) (y : ys) = x * y + scalar xs ys

max' :: [Int] -> Int
max' [] = error "empty list"
max' [x] = x
max' (x:y:z) | x > y = max' (x:z)
             | otherwise = max' (y:z)