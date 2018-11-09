/*
 * Driver for the PCM5102A codec
 *
 * Author:  Florian Meier <florian.meier@koalo.de>
 *      Copyright 2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <sound/soc.h>

static struct snd_soc_dai_driver pcm5102a_dai = {
    .name = "pcm5102a-hifi",
    .playback = {
        .stream_name  = "Playback",
        .channels_min = 1,
        .channels_max = 2,
        .rates = SNDRV_PCM_RATE_8000_96000,
        .formats = (SNDRV_PCM_FMTBIT_S16_LE |
               SNDRV_PCM_FMTBIT_S20_3LE |
               SNDRV_PCM_FMTBIT_S24_3LE |
               SNDRV_PCM_FMTBIT_S32_LE),
    },
};

static struct snd_soc_codec_driver soc_codec_dev_pcm5102a= {

};

static int pcm5102a_probe(struct platform_device *pdev)
{
    printk("PCM5102A probe ...\n");
    return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_pcm5102a,
            &pcm5102a_dai, 1);
}

static int pcm5102a_remove(struct platform_device *pdev)
{
    snd_soc_unregister_codec(&pdev->dev);
    return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id pcm5102a_dt_ids[] = {
    { .compatible = "ti,pcm5102a", },
    { }
};
MODULE_DEVICE_TABLE(of, pcm5102a_dt_ids);
#endif

static struct platform_driver pcm5102a_driver = {
    .probe      = pcm5102a_probe,
    .remove     = pcm5102a_remove,
    .driver     = {
        .name   = "pcm5102a",
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(pcm5102a_dt_ids),
    },
};
module_platform_driver(pcm5102a_driver);

MODULE_DESCRIPTION("ASoC PCM5102A codec driver");
MODULE_AUTHOR("Florian Meier <florian.meier@koalo.de>");
MODULE_LICENSE("GPL v2");