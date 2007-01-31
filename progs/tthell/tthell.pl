#!/usr/bin/perl
## tthell.pl
## Login : <elthariel@.lse.epita.fr>
## Started on  Mon Jan 29 22:14:03 2007 elthariel
## tthell
##
## Copyright (C) 2007 Elthariel
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

##############################################################
######### please forgive me for this ugly code ###############
##############################################################

use strict;

sub main;
sub parse_cmd_line;
sub parse_line;
sub read_file;
sub write_port;

sub make_ttl_header;
sub make_manifest;

my @tthell;
my @manifest;
my @ttl;
# [0] : lv2_name, uri, extensions.
# [x>0][0] : type
#               0 : audio
#               1 : midi
#               2 : control
#       [1] in/out
#       [2] symbol
#       [3] friendly_name
#       [4] type specific.

my $file_tthell;
my $file_ttl;

sub write_port
{
    my $line = $ttl[$_[0]];
    my $index = $_[0];

    print TTL "[\n";
    if ($line->[0] == 0)
    {
        if ($line->[1] =~ /in/) {
            print TTL "a lv2:AudioRateInputPort;\nlv2:datatype lv2:float;\n";
        }
        else {
            print TTL "a lv2:AudioRateOutputPort;\nlv2:datatype lv2:float;\n";
        }
    }
    elsif ($line->[0] == 1)
    {
        if ($line->[1] =~ /in/) {
            print TTL "a lv2:ControlRateInputPort;\nlv2:datatype".
                "<http://ll-plugins.nongnu.org/lv2/ext/miditype>;\n";
        }
        else {
            print TTL "a lv2:ControlRateOutputPort;\nlv2:datatype".
                "<http://ll-plugins.nongnu.org/lv2/ext/miditype>;\n";
        }
    }
    elsif ($line->[0] == 2)
    {
        if ($line->[1] =~ /in/) {
            print TTL "a lv2:ControlRateInputPort;\nlv2:datatype lv2:float;\n";
        }
        else {
            print TTL "a lv2:ControlRateOutputPort;\nlv2:datatype lv2:float;\n";
        }
    }

    print TTL "lv2:index ".$index.";\n";
    print TTL "lv2:symbol \"".$line->[2]."\";\n";
    print TTL "lv2:name \"".$line->[3]."\";\n";

    if ($line->[0] == 2 && defined($line->[4]))
    {
        print TTL "lv2:minimum ".$line->[4].";\n";
        print TTL "lv2:maximum ".$line->[5].";\n";
        print TTL "lv2:default ".$line->[6].";\n";
    }

    print TTL "]";
}

sub make_manifest
{

    open MANIFEST, ">manifest.ttl" or die "Unable to open manifest.tll for writing\n";

    print MANIFEST "\@prefix lv2:  <http://lv2plug.in/ontology#>.\n";
    print MANIFEST "\@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>.\n\n";
    print MANIFEST "<".$ttl[0]->[1].">\n";
    print MANIFEST "lv2:binary <".$ttl[0]->[0].".so>;\n";
    print MANIFEST "rdfs:seeAlso <".$ttl[0]->[0].".ttl>.\n\n";

    close MANIFEST;
}

sub make_ttl_header
{
    open TTL, ">".$ttl[0]->[0].".ttl"
        or die "Unable to open your lv2 ttl file for writing.\n";

    print TTL "\@prefix lv2:  <http://lv2plug.in/ontology#>.\n".
        "\@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#>.\n".
        "\@prefix doap: <http://usefulinc.com/ns/doap#>.\n".
        "\@prefix ll: <http://ll-plugins.nongnu.org/lv2/namespace#>.\n";
    print TTL "\n<".$ttl[0]->[1].">\n";
    print TTL "a lv2:Plugin;\ndoap:name \"".$ttl[0]->[0]."\";\n";
    print TTL "doap:licence <http://usefulinc.com/doap/licenses/gpl>;\n";
    print TTL "ll:gtk2Gui <".$ttl[0]->[0]."_gtk.so>;\n";
    print TTL "lv2:requiredHostFeature ll:instrument-ext;\nll:pegName \"peg\";\n";
    print TTL "\nlv2:port  \n";
}

sub parse_cmd_line
{
    if ($ARGV[0] eq "--help") {
        print "tthell.pl input_file";
    }
    else
    {
        $file_tthell = $ARGV[0];
    }
}

sub read_file
{
    open TTHELL, "<".$file_tthell or die "Unable to open $file_tthell\n";
    @tthell = <TTHELL>;
    close TTHELL;
}

sub parse_line
{
    my @res;
    my $line = $_[0];
    my $i;

    if ($line =~ /^lv2\s+/)
    {
        $line = $';
        while ($line)
        {
            $line =~ /([\S]+)\s*/;
            push @res, $1;
            $line = $';
        }
        $ttl[0] = \@res;
        return;
    }
    elsif ($line =~ /\#/)
    {
        return;
    }
    elsif ($line =~ /(\w+)\s+/)
    {
        if ($1 eq "")
        {
            return;
        }
        elsif ($1 eq "audio")
        {
            $res[0] = 0;
        }
        elsif ($1 eq "midi")
        {
            $res[0] = 1;
        }
        elsif ($1 eq "control")
        {
            $res[0] = 2;
        }
        else
        {
            print "Error : understood nothing\n";
            return;
        }
        $line = $';
        while ($line =~ /(\S+)/)
        {
            push @res, $1;
            $line = $';
        }
        push @ttl, \@res;
        return;
    }
#    $ttl[
}

sub main
{
    my $i;
    my $line;

    $ttl[0] = 0;

    &parse_cmd_line;
    &read_file;
    foreach $line (@tthell)
    {
        &parse_line($line);
    }
    &make_manifest;
    &make_ttl_header;
    for ($i = 1; $i < (scalar @ttl); $i++)
    {
        &write_port($i);
        if ($i == ((scalar @ttl) - 1))
        {
            print TTL ".\n";
        }
        else
        {
            print TTL ",\n\n";
        }
    }
    close TTL;
}

#print $ARGV[0];
&main;
