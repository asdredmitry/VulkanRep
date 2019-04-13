#!/bin/bash
../1.1.101.0/x86_64/bin/glslangValidator -V 09_shader_base.vert 
../1.1.101.0/x86_64/bin/glslangValidator -V 09_shader_base.frag
mv *spv shaders