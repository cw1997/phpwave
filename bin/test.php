<?php
$path = dirname(__dir__).'/phpwave/test.wav';
echo $path."\n";
print_r(phpwave($path));
// var_dump(phpwave($path));