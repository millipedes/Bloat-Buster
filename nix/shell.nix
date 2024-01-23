{ pkgs ? import <nixpkgs> {} }:

let
  cmake = pkgs.cmake;
in

pkgs.mkShell {
  name = "myproject-shell";
  buildInputs = [
    cmake
    pkgs.gcc
  ];
}
