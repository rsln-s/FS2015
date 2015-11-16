mount:
	# 1024 * 1024 = 1048576 = 1mb => 16Mb
	dd if=/dev/zero of=fatdisk bs=1048576 count=16
	mkfs.vfat -c -v -f2 -n FAT16 -r224 -F16 fatdisk
	mkdir fatmnt
	sudo mount -o loop fatdisk fatmnt
	sync
	sync

rpt:
	sudo mount -o loop fatdisk fatmnt

umount:
	sudo umount fatmnt

clean:
	rm -fr fatmnt fatdisk 
