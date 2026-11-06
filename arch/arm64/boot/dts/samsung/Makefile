# SPDX-License-Identifier: GPL-2.0
# Overlays applied by the bootloader on top of qcom/sdm670.dtb

gts4lv-dtbo-$(CONFIG_SEC_GTS4LVWIFI_EUR_PROJECT) += \
	sdm670-sec-gts4lvwifi-eur-overlay-r02.dtbo \
	sdm670-sec-gts4lvwifi-eur-overlay-r03.dtbo \
	sdm670-sec-gts4lvwifi-eur-overlay-r04.dtbo \
	sdm670-sec-gts4lvwifi-eur-overlay-r05.dtbo \
	sdm670-sec-gts4lvwifi-eur-overlay-r06.dtbo \
	sdm670-sec-gts4lvwifi-eur-overlay-r09.dtbo

gts4lv-dtbo-$(CONFIG_SEC_GTS4LV_EUR_PROJECT) += \
	sdm670-sec-gts4lv-eur-overlay-r00.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r01.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r02.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r03.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r04.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r05.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r06.dtbo \
	sdm670-sec-gts4lv-eur-overlay-r09.dtbo

gts4lv-dtbo-$(CONFIG_SEC_GTS4LV_KOR_PROJECT) += \
	sdm670-sec-gts4lv-kor-overlay-r02.dtbo \
	sdm670-sec-gts4lv-kor-overlay-r03.dtbo \
	sdm670-sec-gts4lv-kor-overlay-r04.dtbo \
	sdm670-sec-gts4lv-kor-overlay-r05.dtbo \
	sdm670-sec-gts4lv-kor-overlay-r06.dtbo \
	sdm670-sec-gts4lv-kor-overlay-r09.dtbo

gts4lv-dtbo-$(CONFIG_SEC_GTS4LV_MEA_PROJECT) += \
	sdm670-sec-gts4lv-mea-overlay-r01.dtbo \
	sdm670-sec-gts4lv-mea-overlay-r02.dtbo \
	sdm670-sec-gts4lv-mea-overlay-r03.dtbo \
	sdm670-sec-gts4lv-mea-overlay-r04.dtbo \
	sdm670-sec-gts4lv-mea-overlay-r05.dtbo \
	sdm670-sec-gts4lv-mea-overlay-r06.dtbo \
	sdm670-sec-gts4lv-mea-overlay-r09.dtbo

gts4lv-dtbo-$(CONFIG_SEC_GTS4LV_USA_PROJECT) += \
	sdm670-sec-gts4lv-usa-overlay-r04.dtbo \
	sdm670-sec-gts4lv-usa-overlay-r05.dtbo \
	sdm670-sec-gts4lv-usa-overlay-r06.dtbo \
	sdm670-sec-gts4lv-usa-overlay-r07.dtbo \
	sdm670-sec-gts4lv-usa-overlay-r08.dtbo

$(obj)/%.dtbo: $(src)/%.dts $(DTC) FORCE
	$(call if_changed_dep,dtc)

always		:= $(gts4lv-dtbo-y)
clean-files	:= *.dtbo
