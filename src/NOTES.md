
## Decoders

    ffmpeg -hide_banner -decoders

### print info about decoder

    ffmpeg -hide_banner -h decoder=<decoder name>
    $ ffmpeg -hide_banner -h decoder=h264

### print all video decoders names

    ffmpeg -hide_banner -decoders | grep "V....D" | awk '{print $2}'

### print all audio decoders names

    ffmpeg -hide_banner -decoders | grep "A....D" | awk '{print $2}'

## Encoders

    ffmpeg -hide_banner -encoders

### print info about encoder

    ffmpeg -hide_banner -h decoder=<encoder name>
    $ ffmpeg -hide_banner -h encoder=h264

### print all video decoders names

    ffmpeg -hide_banner -encoders | grep "V....D" | awk '{print $2}'

### print all audio decoders names

    ffmpeg -hide_banner -encoders | grep "A....D" | awk '{print $2}'

### thumbnails from video in k directory, 0.03 defines

    - https://superuser.com/questions/538112/meaningful-thumbnails-for-a-video-using-ffmpeg
    - https://copyprogramming.com/howto/extract-thumbnail-in-ffmpeg-code-example

    `ffmpeg -i l.webm -vf "thumbnail,select=gt(scene\,0.03)" -vsync vfr k/out%d.jpg`

