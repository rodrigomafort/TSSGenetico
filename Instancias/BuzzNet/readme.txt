Social Computing Data Repository - Basic Information
==========================================================================
Dataset Name: BuzzNet
Abstract: Buzznet is a photo, journal, and video-sharing social media network.
Number of Nodes: 101,168
Number of Edges: 4,284,534
Missing Values: No

Data Set Information:
==========================================================================
[I]. Brief description
This is the data set crawled on Nov, 2010 from Buzznet. Buzznet is a photo, journal, and video-sharing social media network. 
This contains the friendship network crawled. For easier understanding, all the contents are organized in CSV file format.

[II]. Basic statistics
Number of users : 101,168
Number of friendship pairs: 4,284,534

[III]. The data format

2 files are included:

1. nodes.csv
-- it's the file of all the users. This file works as a dictionary of all the users in this data set. It's useful for fast reference. It contains
all the node ids used in the dataset

2. edges.csv
-- this is the friendship network among the bloggers. The blogger's friends are represented using edges. Here is an example. 

1,2

This means blogger with id "1" is friend with blogger id "2".