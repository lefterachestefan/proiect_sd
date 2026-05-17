{
  description = "C++ Sorting Algorithms Project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            clang_18
            cmake
            ninja
            gnumake
            python3
            luau
          ];
          buildInputs = with pkgs; [
          ];
          shellHook = ''
            export CC=clang
            export CXX=clang++
          '';
        };
      }
    );
}
