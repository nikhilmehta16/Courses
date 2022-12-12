
data Var = U | V | W | X | Y | Z deriving (Eq, Show)
data Fun = A | B | C | D | E | F | G | H | I | J deriving (Eq, Show)
data Gtree = Gnode Fun [Gtree] | Leafv Var deriving (Eq, Show)
type Term = Gtree


inTree :: Var -> Term -> Bool
inTree a (Leafv b) = a == b
inTree var (Gnode fun xs) = any (inTree var) xs

singlefdouble :: [[a]] -> [a]
singlefdouble = foldl (++) []

unify ::(Term, Term) -> [(Var, Term)]

unify (Leafv a, lf@(Leafv v2)) = (a, lf):[]
unify (Leafv a, gn@(Gnode fun xs)) =
    if a `inTree` gn
    then error "Infinite MGU"
    else (a, gn):[]
    
unify (gn@(Gnode fun xs), lf@(Leafv v1)) = unify (lf, gn)
unify (Gnode fun1 xs1, Gnode fun2 xs2)
  | fun1 /= fun2 = error "MGU not possible"
  | (length xs1) /= (length xs2) = error "MGU not possible"
  | otherwise = reverse (singlefdouble (map unify (zip xs1 xs2)))
  