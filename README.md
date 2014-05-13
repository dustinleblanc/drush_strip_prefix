# WARNING: 
This command has the potential to completely FUBAR your database, I have very *_MINIMALLY_* tested this command at this point and it borrows ideas from different scripts I have run accross. After running this command you going to have to manually edit your settings file to correct your prefixes. This approach is probably really dangerous and can break many things. You have been warned.


## Installation

1. clone this repo into your .drush folder, probably like this:

`git clone git@github.com:dustinleblanc/drush_strip_prefix.git ~/.drush/strip_prefix`

2. Clear your drush cache: `drush cc drush`


You should now see the command come up if you run something like:  `drush | grep strip`

You can now execute the command like so: `drush strip foo_` to strip the 'foo_' prefix from a set of databases.

## SECOND WARNING:

Really, I haven't tested this much yet, so be realllllly careful, its not stable until it has been tested further. This command will give one chance to confirm you really meant it, then go at your database like chainsaw massacre style, you have been warned...again!

Pull requests are welcome :)
