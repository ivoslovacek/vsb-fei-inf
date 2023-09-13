data Tree a = Leaf a
            | Branch a (Tree a) (Tree a) deriving (Show)

testTree1 :: Tree Int            
testTree1 = Branch 12 (Branch 23 (Leaf 34) (Leaf 45)) (Leaf 55)

sum' :: Tree Int -> Int
sum' (Leaf x) = x
sum' (Branch x y z) = x + sum' y + sum' z

toList :: Tree a -> [a]
toList (Leaf x) = [x]
toList (Branch x y z) = [x] ++ toList y ++ toList z

toString :: Show a => Tree a -> String
toString (Leaf x) = show x
toString (Branch x y z) = show x ++ "(" ++ toString y ++ "," ++ toString z ++ ")"

fromString :: Read a => String -> Tree a
fromString inp = fst (fromString' inp) where
  fromString' :: Read a => String -> (Tree a,String)
  fromString' inp = 
    let
      before = takeWhile (\x ->  x /='(' &&  x /=',' &&  x/=')') inp 
      after = dropWhile (\x ->  x /='(' &&  x /=',' && x/=')') inp
      value = read before
    in if null after || head after /= '(' then (Leaf value, after) else 
        let
          (l,after') = fromString' (tail after)
          (r,after'') = fromString' (tail after') 
        in (Branch value l r, tail after'')
        