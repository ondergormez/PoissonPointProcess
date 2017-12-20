#!/usr/bin/perl
#
# Use PoissonPointProcess
# Shared Lib on Octave
#

use strict;
use warnings;
use Cwd;

my $CURRENT_DIR = cwd();
my $ARGUMENT_NAME = "tttest.m";

chdir './_ignore_obj';
system(sprintf("octave $ARGUMENT_NAME"));
