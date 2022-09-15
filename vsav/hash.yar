import "hash"

rule hash {

        meta:
		author = "Stian K"
                version = "1.0"

        condition:
		hash.md5(0,filesize) == "8cd5cbdf7c79598c38a2cf67b84bb081"
		and filesize == 3293500
}
