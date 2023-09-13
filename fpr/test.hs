data Component = TextBox {name :: String, text :: String}
                | Button {name :: String, value :: String}
                | Container {name :: String, children :: [Component]} deriving Show

gui :: Component
gui = Container "My App" [
    Container "Menu" [
        Button "btn_new" "New",
        Button "btn_open" "Open",
        Button "btn_close" "Close"
    ],
    Container "Body" [TextBox "textbox_1" "Some text goes here"],
    Container "Footer" []]

btnCount :: Component -> Int
btnCount (TextBox _ _) = 0
btnCount (Button _ _) = 1
btnCount (Container _ x) = sum (map btnCount x)

listAllNames :: Component -> [String]
listAllNames (TextBox x _) = [x]
listAllNames (Button x _) = [x]
listAllNames (Container x y) = x : concatMap listAllNames y

listAllButtons :: Component -> [String]
listAllButtons (TextBox _ text) = [text]
listAllButtons (Button _ _) = []
listAllButtons (Container _ y) = concatMap listAllButtons y

addElement :: Component -> Component -> String -> Component
addElement (TextBox x y) new name = (TextBox x y)
addElement (Button x y) new name = (Button x y)
addElement (Container x y) new name | x == name = Container x (y++[new])
                                    | otherwise = Container x [addElement x new name | x <- y]