#!/usr/bin/perl
## bang.pl
## Login : <elthariel@free.fr>
## Started on  Fri Dec 15 06:09:21 2006 Elthariel
## $Id$
##
## Copyright (C) 2006 Elthariel
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

use strict;
use Image::Magick;

# ./script.pl size_x size_y margin
#
# This script creates the 127 image states of a vertical slider.
#
#

sub draw_back;
sub draw_front;

my $img = Image::Magick->new();

sub draw_back
{
    my ($frame, $state) = @_;

    my $tmp = int($ARGV[0] / 8);
    my @p;
    my $str;

    $p[0] = $tmp * 3;
    $p[1] = 15;
    $p[2] = $tmp * 5;
    $p[3] = $ARGV[1] - 15;
    $str = $p[0] . ',' . $p[1] . ' ' . $p[2] . ',' . $p[3];

    $frame->Draw(primitive => 'rectangle', fill => 'white', points => $str,
                 method => 'FillToBorder');
}

sub draw_front
{
    my ($frame, $state, $cursor_x, $cursor_y) = @_;
    my $points;
    my $cursor_pos_y;
    my $cursor_pos_x;

    $cursor_pos_y = int(($ARGV[1] - 30) * (1 - ($state / 127))) + 15;
    $cursor_pos_x = int($ARGV[0] / 2);
    $points = ($cursor_pos_x - $cursor_x) . ',' . ($cursor_pos_y - $cursor_y)
        . ' ' . ($cursor_pos_x + $cursor_x) . ',' . ($cursor_pos_y + $cursor_y);

    $frame->Draw(primitive => 'rectangle', fill => 'DarkOliveGreen', points => $points,
                 method => 'FillToBorder');
}

for (my $i = 0; $i < 128; $i++)
{
    my $frame;

    $frame = Image::Magick->new(size=>$ARGV[0].'x'.$ARGV[1], background=>'white', pointsize=>30, fill=>'black');
    $frame->Read('xc:white');

    $frame->Colorize(fill => 'transparent');

    draw_back($frame, $i);
    $frame->Blur(radius=>'10.0');
    draw_front($frame, $i, 30, 10);
    $frame->Blur(radius=>'0.5');

    push(@$img, $frame);
}

$img->Write("imgs/fader.png");
