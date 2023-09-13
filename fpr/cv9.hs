data Expr = Num Int
          | Add Expr Expr
          | Sub Expr Expr
          | Mul Expr Expr
          | Div Expr Expr
          | Var Char
       deriving (Eq)

instance (Show Expr) where
   show = showExpr

eval :: Expr -> Int
eval (Num x) = x
eval (Add x y) = (eval x) + (eval y)
eval (Sub x y) = (eval x) - (eval y)
eval (Mul x y) = (eval x) * (eval y)
eval (Div x y) = (eval x) `div` (eval y)

charToString :: Char -> String
charToString x = [x]

showExpr :: Expr -> String
showExpr (Var x) = charToString x
showExpr (Num x) = show x
showExpr (Add x y) = showExpr x ++ "+" ++ showExpr y
showExpr (Sub x y) = showExpr x ++ "-" ++ showExpr y
showExpr (Mul x y) = showExpr x ++ "*" ++ showExpr y
showExpr (Div x y) = showExpr x ++ "/" ++ showExpr y