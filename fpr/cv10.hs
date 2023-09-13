data Tree a = Leaf a| Branch a (Tree a) (Tree a)

myTree :: Tree Int
myTree = Branch 4 (Branch 8 (Leaf 1) (Branch 8 (Leaf 7) (Leaf 5))) (Leaf 9)

testTree2 :: Tree Char
testTree2 = Branch 'a' (Branch 'b' (Leaf 'c') (Leaf 'd')) (Leaf 'e')

sum' :: Tree Int -> Int
sum' (Leaf x) = x
sum' (Branch x y z) = x + sum' y + sum' z

toList :: Tree a -> [a]
toList (Leaf x) = [x]
toList (Branch x y z) = [x] ++ toList y ++ toList z

toString :: Show a => Tree a -> String
toString (Leaf x) = show x
toString (Branch x y z) = show x ++ "(" ++ toString y ++ "," ++ toString z ++ ")"
