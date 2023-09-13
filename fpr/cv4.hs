take' :: Int -> [a] -> [a]
take' 0 _      = []
take' _ []     = []
take' n (x:xs) = x : take' (n - 1) xs

drop' :: Int -> [a] -> [a]
drop' 0 x      = x
drop' _ []     = []
drop' n (x:xs) = drop' (n - 1) xs

minimum' :: Ord a => [a] -> a
minimum' [] = error "empty list"
minimum' [x] = x
minimum' (x:y:ys) | y < x = minimum' (y:ys)
                  | x < y = minimum' (x:ys)

divisors :: Int -> [Int]
divisors 0 = []
divisors n = tmp n where
    tmp 0 = []
    tmp x | n `mod` x == 0 = x: tmp (x-1)
          | otherwise = tmp (x-1)

zipThem :: [a] -> [b]  -> [(a,b)]
zipThem _ []          = []
zipThem [] _          = []
zipThem (a:as) (b:bs) = (a,b) : zipThem as bs

dotProduct :: [a] -> [b]  -> [(a,b)]
dotProduct [] _ = []
dotProduct (x:xs) ys = tmp ys ++ dotProduct xs ys where
  tmp []     = []
  tmp (b:bs) = (x,b) : tmp bs

fibonacci :: Int -> Int
fibonacci n = fst (tmp n) where
  fibStep (a,b) = (b,a+b)
  tmp 0 = (0,1)
  tmp x = fibStep (tmp (x-1))

idk :: (Integral a) =>[a] -> [b] -> [(a,b)]
idk xs ys = [(x,y) | x <- xs, x<3, y <- ys]