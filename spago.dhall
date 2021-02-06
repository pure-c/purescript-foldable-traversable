{ name = "foldable-traversable"
, dependencies =
  [ "bifunctors"
  , "control"
  , "maybe"
  , "newtype"
  , "orders"
  , "prelude"
  , "assert"
  , "console"
  , "integers"
  , "math"
  , "unsafe-coerce"
  ]
, packages = ../pure-c/package-sets/packages.dhall
, sources = [ "src/**/*.purs", "test/**/*.purs" ]
}
