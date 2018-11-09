/*
 * ASoC codec driver for DSP56725
 *
 * sound/soc/codecs/dsp56725.c -- ALSA SoC DSP56725 codec driver
 *
 * Copyright (C) 2018 Phan Le Son <plson03.com>
 *
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/clk.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pm.h>
#include <linux/regmap.h>
#include <linux/slab.h>

#include <sound/core.h>
#include <sound/initval.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/tlv.h>



#define DSP56725_RATES		(SNDRV_PCM_RATE_48000)
#define DSP56725_FORMAT		( SNDRV_PCM_FMTBIT_S24_3LE )



static struct snd_soc_dai_driver dsp56725_dai = {
	.name = "dsp56725-audio",
	.capture = {
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 30,
		.rates = DSP56725_RATES,
		.formats = DSP56725_FORMAT,
	},

};

static const struct snd_soc_dapm_widget pcm3168_dapm_widgets[] = {

SND_SOC_DAPM_INPUT("VIN1"),
SND_SOC_DAPM_INPUT("VIN2"),
SND_SOC_DAPM_INPUT("VIN3"),
SND_SOC_DAPM_INPUT("VIN4"),
SND_SOC_DAPM_INPUT("VIN5"),
SND_SOC_DAPM_INPUT("VIN6"),

SND_SOC_DAPM_INPUT("VIN7"),
SND_SOC_DAPM_INPUT("VIN8"),
SND_SOC_DAPM_INPUT("VIN9"),
SND_SOC_DAPM_INPUT("VIN10"),
SND_SOC_DAPM_INPUT("VIN11"),
SND_SOC_DAPM_INPUT("VIN12"),

SND_SOC_DAPM_INPUT("VIN13"),
SND_SOC_DAPM_INPUT("VIN14"),
SND_SOC_DAPM_INPUT("VIN15"),
SND_SOC_DAPM_INPUT("VIN16"),
SND_SOC_DAPM_INPUT("VIN17"),
SND_SOC_DAPM_INPUT("VIN18"),

SND_SOC_DAPM_INPUT("VIN19"),
SND_SOC_DAPM_INPUT("VIN20"),
SND_SOC_DAPM_INPUT("VIN21"),
SND_SOC_DAPM_INPUT("VIN22"),
SND_SOC_DAPM_INPUT("VIN23"),
SND_SOC_DAPM_INPUT("VIN24"),

SND_SOC_DAPM_INPUT("VIN25"),
SND_SOC_DAPM_INPUT("VIN26"),
SND_SOC_DAPM_INPUT("VIN27"),
SND_SOC_DAPM_INPUT("VIN28"),
SND_SOC_DAPM_INPUT("VIN29"),
SND_SOC_DAPM_INPUT("VIN30"),
};

static const struct snd_soc_dapm_route pcm3168_dapm_routes[] = {

	{ "VIN1", NULL, "Capture" },
	{ "VIN2", NULL, "Capture" },
	{ "VIN3", NULL, "Capture" },
	{ "VIN4", NULL, "Capture" },
	{ "VIN5", NULL, "Capture" },
	{ "VIN6", NULL, "Capture" },

	{ "VIN7", NULL, "Capture" },
	{ "VIN8", NULL, "Capture" },
	{ "VIN9", NULL, "Capture" },
	{ "VIN10", NULL, "Capture" },
	{ "VIN11", NULL, "Capture" },
	{ "VIN12", NULL, "Capture" },

	{ "VIN13", NULL, "Capture" },
	{ "VIN14", NULL, "Capture" },
	{ "VIN15", NULL, "Capture" },
	{ "VIN16", NULL, "Capture" },
	{ "VIN17", NULL, "Capture" },
	{ "VIN18", NULL, "Capture" },

	{ "VIN19", NULL, "Capture" },
	{ "VIN20", NULL, "Capture" },
	{ "VIN21", NULL, "Capture" },
	{ "VIN22", NULL, "Capture" },
	{ "VIN23", NULL, "Capture" },
	{ "VIN24", NULL, "Capture" },

	{ "VIN25", NULL, "Capture" },
	{ "VIN26", NULL, "Capture" },
	{ "VIN27", NULL, "Capture" },
	{ "VIN28", NULL, "Capture" },
	{ "VIN29", NULL, "Capture" },
	{ "VIN30", NULL, "Capture" },

};


static const struct snd_soc_codec_driver dsp56725_codec_driver = {
	.dapm_widgets		= pcm3168_dapm_widgets,
	.num_dapm_widgets	= ARRAY_SIZE(pcm3168_dapm_widgets),
	.dapm_routes		= pcm3168_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm3168_dapm_routes),

};


static int dsp56725_probe(struct platform_device *pdev)
{

	int ret;

  	printk("dsp56725: probing \n");
        printk("------------------------------------------------------ \n");


	ret = snd_soc_register_codec(&pdev->dev,
			&dsp56725_codec_driver, &dsp56725_dai, 1);
	if (ret != 0)
		dev_err(&pdev->dev, "Failed to register CODEC: %d\n", ret);

        return ret;
}

static int dsp56725_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);

	return 0;
}



#if defined(CONFIG_OF)
static const struct of_device_id dsp56725_of_match[] = {
	{ .compatible = "ti,dsp56725", },
        { } 
};
MODULE_DEVICE_TABLE(of, dsp56725_of_match);
#endif


static struct platform_driver dsp56725_driver = {
	.driver = {
		.name = "dsp56725",
		.owner = THIS_MODULE,
    		.of_match_table = of_match_ptr(dsp56725_of_match),
	},
	.probe		= dsp56725_probe,
	.remove		= dsp56725_remove,
};

module_platform_driver(dsp56725_driver);

MODULE_DESCRIPTION("DSP57625 codec driver");
MODULE_AUTHOR("Phan Le Son <plson03@gmail.com>");
MODULE_LICENSE("GPL");
