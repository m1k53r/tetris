{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [ pkgs.gcc pkgs.neovim pkgs.git pkgs.ncurses pkgs.fish pkgs.gnumake ];
}
