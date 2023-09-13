data Point = Point Int Int
data Triangle = Triangle Point Point Point

type Result = [String]

pp :: Result -> IO ()
pp x = putStr (concat (map (++"\n") x))

drawTriangles :: (Int,Int) -> [Triangle] -> Result
drawTriangles 