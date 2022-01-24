{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [ pkgs.gcc pkgs.neovim pkgs.git pkgs.ncurses pkgs.fish pkgs.gnumake pkgs.sqlite pkgs.git ];
}
